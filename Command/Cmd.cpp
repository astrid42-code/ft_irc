#include "Cmd.hpp"

Cmd::Cmd(): _server(NULL), _user(NULL), _key(""), _size(0)
{
	// build les fcts cmds en reliant une string a la fct ou plutot faire un make_pair()?

	// basic cmds
	_cmd["NICK"] = nick;
	_cmd["USER"] = user;
	_cmd["QUIT"] = quit;
	_cmd["MODE"] = mode;

	// channel cmds
	_cmd["JOIN"] = join;
	_cmd["PART"] = part;
	_cmd["LIST"] = list;

	// advanced cmds
	_cmd["PRIVMSG"] = privmsg;
	_cmd["NOTICE"] = notice;
	_cmd["WHO"] = who;

	_cmd["INVITE"] = invite;
	_cmd["KICK"] = kick;
	_cmd["OPER"] = oper;
	_cmd["KILL"] = kill;
	_cmd["WHOIS"] = whois;
	_cmd["PASS"] = pass;
	_cmd["PING"] = ping;
	_cmd["AWAY"] = away;
}

Cmd::Cmd(const Cmd & cp)
{
	*this = cp;
}

Cmd::~Cmd()
{
	// clear ?
	std::cout << "Command destroyed..." << std::endl;
}

Cmd & Cmd::operator=(const Cmd &cmd_op)
{
	_cmd = cmd_op._cmd;
	return (*this);
}

void Cmd::set_key(std::string key)
{
	_key = key;
}

const std::string	Cmd::get_key(void) const
{
	return (_key);
}

void Cmd::set_value(std::vector<std::string> value)
{
	_value = value;
}

std::vector<std::string>	Cmd::get_value(void) const
{
	// std::cout << "get value"  << std::endl;
	return (_value);
}

void	Cmd::set_size(int i)
{
	_size = i;
}

int		Cmd::get_size(void) const
{
	return (_size);
}

int		check_condition(std::string key)
{
	if (key.compare("JOIN") == 0 || key.compare("USER") == 0 || key.compare("INVITE") == 0
			|| key.compare("KICK") == 0 || key.compare("NICK") == 0 || key.compare("OPER") == 0 || key.compare("QUIT") == 0 
			|| key.compare("KILL") == 0 || key.compare("PRIVMSG") == 0 || key.compare("WHO") == 0 || key.compare("WHOIS") == 0
			|| key.compare("LIST") == 0 || key.compare("PASS") == 0 || key.compare("NAMES") == 0 || key.compare("PING") == 0
			|| key.compare("PART") == 0 || key.compare("MODE") == 0 || key.compare("AWAY") == 0 || key.compare("NOTICE") == 0)
		return (1);
	return (0);
}

User *Cmd::get_user_fd()
{
	std::map<int, User *> tmp = _server->get_users();
	std::map<int, User *>::iterator it = tmp.find(_sfd);

	// std::cout << "get_user_fd" << std::endl;
	// if (!_server->get_users().empty())
	// {
		// it = _server->get_users().find(_sfd);

		if (it == tmp.end())
		{
			// std::cout << "user not found" << std::endl;
			return (NULL);
		}
		else
		{
			// std::cout << "user found" << std::endl;
			return (it->second);
		}
	// }
	return (NULL);
}

void Cmd::parse_cmd(std::string str)
{
	std::string key; // pour recuperer la key (1er mot de str)
	size_t start;
	size_t end = 0;
	size_t size;
	std::string tmp_val;
	std::string	trailing;
	int tmp = 0;
	std::cout << "parse_cmd" << std::endl;
	key = str.substr(0, str.find(' '));
	size = str.size() - key.size();
	if (check_condition(key))
	{
		std::cout << "check key done" << std::endl;
		set_key(key);
		if (size == 0)
		{
			set_size(0);
			_cmd[_key](*this);
			return;
		}
		tmp_val = str.substr(str.find(' '), str.size());
		while ((start = tmp_val.find_first_not_of(' ', end)) != std::string::npos)
		{
			end = tmp_val.find(' ', start);
			if (tmp_val.find(':', start) != std::string::npos && tmp_val.find(':', start) < end)
				break ;
			_value.push_back(tmp_val.substr(start, end - start));
			std::cout << "_value" << tmp << " = " << _value[tmp] << std::endl;
			tmp++;
		}
		if (tmp_val.find(':') != std::string::npos)
		{
			trailing = tmp_val.substr(tmp_val.find(':') + 1, tmp_val.find("\r\n") - tmp_val.find(':') + 1);
			_value.push_back(trailing);
			tmp++;
			std::cout << "tvalue" << tmp << " = " << _value.back() << std::endl;
		}
		set_size(tmp);
		_cmd[_key](*this);
	}
}

void	Cmd::print(void)
{
	std::vector<std::string>::iterator it = _value.begin();

	std::cout << "key: " + _key << std::endl;
	while (it != _value.end())
	{
		std::cout << it->data() << std::endl;
		it++;
	}
	if (_user)
		_user->print();
	else
	 	std::cout << "no user" << std::endl;
	// if (_server)
	// 	std::cout << _server->print() << std::endl;
	// else
	// 	std::cout << "no server" << std::endl;
	std::cout << "end of Cmd.print()" << std::endl;
}

// - AWAY
// - ISON
// - USERHOST
// - USERS (handled but disabled)
// - WALLOPS
// - NOTICE
// - 
// - ADMIN
// - INFO
// - LUSERS
// - MOTD
// - TIME
// - VERSION
// - WHOWAS


// https://mathieu-lemoine.developpez.com/tutoriels/irc/protocole/?page=page-4