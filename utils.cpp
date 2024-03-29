/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:23:54 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:24:04 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"

void	pre_parse(std::string buf, int sfd, Server *serv)
{
	std::size_t pos = 0;
	std::string token;

	User *usr = serv->get_user(sfd);
	if (usr == NULL)
		return;
	usr->buf.append(buf);
	while (usr != NULL && pos < usr->buf.length() && usr->buf.find("\r\n", pos) != std::string::npos)
	{

		// std::cout << "Command " << std::endl;
		Cmd *command = new Cmd();
		// std::cout << "serv " << std::endl;
		command->_server = serv;
		// std::cout << "sfd " << std::endl;
		command->_sfd = sfd;
		// std::cout << "get_user_fd " << std::endl;
		command->_user = command->get_user_fd();
		if (command->_user == NULL)
			std::cout << "_____NoUserFromFd_____" << std::endl;
		else
		{
			std::cout << "_____UserFromFd_____" << std::endl;
			std::cout << command->_user << std::endl;
		}
		if ((usr->buf.find("\r\n", pos)) != std::string::npos)
		{
			token = usr->buf.substr(pos, usr->buf.find("\r\n", pos) - pos);
			usr->buf = usr->buf.substr(usr->buf.find("\r\n", pos) + 2);
		}
		else
			pos = usr->buf.length();
		std::cout << "token :|" << token << "|" << std::endl;
		command->parse_cmd(token);
		usr = serv->get_user(sfd);
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
	return (res);
}

bool	mask_off(std::string mask, std::string str)
{
	std::vector<std::string>	mask_div;
	std::size_t					i = 0;
	std::size_t					j;
	std::size_t					n = 0;

	while (i < mask.length())
	{
		j = i;
		if ((i = mask.find("*")) != std::string::npos)
			mask_div.push_back(mask.substr(j, i++ - j));
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
			return (false);
		else
			n++;
	}
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

std::string to_upper(std::string str)
{
	char tmp;
	std::string ret;
	size_t i = 0;

	while (i < str.length())
	{
		if (str.c_str()[i] >= 'a' && str.c_str()[i] <= 'z')
			tmp = str.c_str()[i] - 32;
		else 
			tmp = str.c_str()[i];
		ret.push_back(tmp);
		i++;
	}
	return (ret);
}

bool	erase_chan(Channel *chan, User *user)
{
	if (chan->get_users().empty() || (user != NULL && chan->get_users().size() == 1 && chan->get_user(user->get_nick()) == user))
		return (true);
	return (false);
}