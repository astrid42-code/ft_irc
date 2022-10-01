#include "Cmd.hpp"

Cmd::Cmd(): _server(NULL), _user(NULL), _key(""), _size(0)
{
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
	_cmd["PING"] = pong;
	_cmd["PONG"] = ping;
	_cmd["AWAY"] = away;
}

Cmd::Cmd(const Cmd & cp)
{
	*this = cp;
}

Cmd::~Cmd()
{}

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

User *Cmd::get_user_fd()
{
	std::map<int, User *> *tmp = _server->get_users();
	std::map<int, User *>::iterator it = tmp->find(_sfd);

	if (it == tmp->end())
		return (NULL);
	else
		return (it->second);
	return (NULL);
}

void Cmd::parse_cmd(std::string str)
{
	std::string key;
	size_t start;
	size_t end = 0;
	size_t size;
	std::string tmp_val;
	std::string	trailing;
	int tmp = 0;

	key = str.substr(0, str.find(' '));
	size = str.size() - key.size();
	if (check_condition(*this, key))
	{
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
			tmp++;
		}
		if (tmp_val.find(':') != std::string::npos)
		{
			trailing = tmp_val.substr(tmp_val.find(':') + 1, tmp_val.find("\r\n") - tmp_val.find(':') + 1);
			_value.push_back(trailing);
			tmp++;
		}
		set_size(tmp);
		_cmd[_key](*this);
	}
}

// void	Cmd::print(void)
// {
// 	std::vector<std::string>::iterator it = _value.begin();

// 	while (it != _value.end())
// 	{
// 		std::cout << it->data() << std::endl;
// 		it++;
// 	}
// 	if (_user)
// 		_user->print();
// 	else
// 	 	std::cout << "no user" << std::endl;
// 	std::cout << "end of Cmd.print()" << std::endl;
// }

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