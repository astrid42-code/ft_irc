#include "Server/Server.hpp"

void	pre_parse(std::string buf, int sfd, Server *serv)
{
	std::size_t pos = 0;
	std::string token;
	std::string pre_buf = "";

	std::cout << "buf = " << buf << std::endl;
	pre_buf.append(buf);
	while (pos < pre_buf.length() && pre_buf.find("\r\n", pos) != std::string::npos)
	{
		std::cout << "while loop preparse" << std::endl;
		Cmd *command = new Cmd();
		command->_server = serv;
		command->_sfd = sfd;
		command->_user = command->get_user_fd();
		if (std::time(NULL) - command->_server->get_time() > TIME_LIMIT)
		{
			std::cout << "going to ping ?" << std::endl;
			ping(*command);
		} // timer to ping user
		if (command->_user == NULL)
		{
			std::cout << "_____NoUserFromFd_____" << std::endl;
			pos = pre_buf.length();
		}
		else
		{
			std::cout << "_____UserFromFd_____" << std::endl;
			command->_user->print();
			if ((pre_buf.find("\r\n", pos)) != std::string::npos)
			{
				token = pre_buf.substr(pos, pre_buf.find("\r\n", pos) - pos);
				pre_buf = pre_buf.substr(pre_buf.find("\r\n", pos) + 2);
			}
			else
				pos = pre_buf.length();
			std::cout << "token :|" << token << "|" << std::endl;
			command->parse_cmd(token);
		}
		delete command;
	}
}

std::vector<std::string>	div_string(std::string str, char c)
{
	std::vector<std::string>	res;
	size_t						n = 0;
	size_t 						i = 0;

	while (str[i])
	{
		if (str[i] == c)
		{
			res.push_back(str.substr(n, i - n));
			n = ++i;
		}
		i++;
	}
	res.push_back(str.substr(n, str.length()));
	std::cout << "div_string :" << std::endl;
	for (std::vector<std::string>::iterator it = res.begin(); it != res.end(); it++)
	{
		std::cout << "|" << *it << "|" << std::endl;
	}
	return (res);
}

bool	mask_off(std::string mask, std::string str)
{
	std::vector<std::string>	mask_div;
	std::size_t					i = 0;
	std::size_t					j;
	std::size_t					n = 0;

	std::cout << "mask_off ok ?" << std::endl;
	while (i < mask.length())
	{
		j = i;
		if ((i = mask.find("*")) != std::string::npos)
		{
			mask_div.push_back(mask.substr(j, i++ - j));
			std::cout << "|" << mask_div.back() << "|" << std::endl;
		}
		else
			i = mask.length();
	}
	if (mask_div.empty())
		mask_div.push_back(mask);
	i = 0;
	while (n < mask_div.size())
	{
		j = i;
		if (!mask_div[n].empty() && (i = str.find(mask_div[n], j)) == std::string::npos)
		{
			std::cout << "false :" << mask_div[n] << std::endl;
			return (false);
		}
		else
			n++;
	}
	std::cout << "mask_off ok" << std::endl;
	return (true);
}

int		check_condition(Cmd &command, std::string key)
{
	if (key.compare("PASS") == 0 && command._user->get_valid() == 0)
		return (1);
	else if (key.compare("NICK") == 0 && (command._user->get_valid() == 1 || command._user->get_valid() == 3))
		return (1);
	else if (key.compare("USER") == 0 && command._user->get_valid() == 2)
		return (1);
	else if (command._user->get_valid() == 3 && (key.compare("JOIN") == 0 || key.compare("INVITE") == 0
			|| key.compare("KICK") == 0 || key.compare("OPER") == 0 || key.compare("QUIT") == 0 
			|| key.compare("KILL") == 0 || key.compare("PRIVMSG") == 0 || key.compare("WHO") == 0
			|| key.compare("LIST") == 0 || key.compare("NAMES") == 0 || key.compare("PING") == 0
			|| key.compare("PART") == 0 || key.compare("MODE") == 0 || key.compare("AWAY") == 0
			|| key.compare("WHOIS") == 0 || key.compare("NOTICE") == 0))
		return (1);
	return (0);
}

// fct pour savoir s'il faut erase le channel (s'il est empty de users : erase)
bool	erase_chan(Channel *chan, User *user)
{
	if (chan->get_users().empty() || (user != NULL && chan->get_users().size() == 1 && chan->get_user(user->get_nick()) == user)) // si le vector _users est empty
		return (true);
	return (false); // s'il reste des users
}