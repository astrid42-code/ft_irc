/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whois.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:04:08 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:14:45 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

//       Command: WHOIS
//    Parameters: [ <target> ] <mask> *( "," <mask> )
							   
void	whois(Cmd &command)
{
	bool						user_found = false;
	User						*user = NULL;
	std::map<int, User *>		*users = command._server->get_users();
	std::vector<std::string>	args;

	if (command.get_size() == 1)
	{
		args = div_string(command.get_value()[0], ',');
		for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
		{
			if (it->find("*") != std::string::npos)
			{
				for (std::map<int, User *>::iterator at = users->begin(); at != users->end(); at++)
				{
					if (at->second && !at->second->find_mod("i") && mask_off(*it, at->second->get_hostname()))
					{
						if (at->second->find_mod("a"))
							command._server->send_msg(RPL_AWAY(command._user->get_hostname(), at->second->get_nick(), at->second->get_away()), command._sfd);
						command._server->send_msg(RPL_WHOISUSER(command._user->get_hostname(), at->second->get_nick(), at->second->get_user(), at->second->get_host(), at->second->get_name()), command._sfd);
						if (at->second->find_mod("o"))
							command._server->send_msg(RPL_WHOISOPERATOR(command._user->get_hostname(), at->second->get_nick()), command._sfd);
						user_found = true;
					}
				}
			}
			else
			{
				if ((user = command._server->get_user(*it)) != NULL)
				{
					if (!user->find_mod("i"))
					{
						if (user->find_mod("a"))
							command._server->send_msg(RPL_AWAY(command._user->get_hostname(), user->get_nick(), user->get_away()), command._sfd);
						command._server->send_msg(RPL_WHOISUSER(command._user->get_hostname(), user->get_nick(), user->get_user(), user->get_host(), user->get_name()), command._sfd);
						if (user->find_mod("o"))
							command._server->send_msg(RPL_WHOISOPERATOR(command._user->get_hostname(), user->get_nick()), command._sfd);
						user_found = true;
					}
				}
				else
					command._server->send_msg(ERR_NOSUCHNICK(command._user->get_hostname(), *it, ""), command._sfd);
			}
		}
	}
	else if (command.get_size() == 2)
		command._server->send_msg(ERR_NOSUCHSERVER(command._user->get_hostname(), command.get_value()[0]), command._sfd);
	else
		command._server->send_msg(ERR_NONICKNAMEGIVEN(command._user->get_hostname()), command._sfd);
	if (user_found)
		command._server->send_msg(RPL_ENDOFWHOIS(command._user->get_hostname(), command._user->get_nick()), command._sfd);
}