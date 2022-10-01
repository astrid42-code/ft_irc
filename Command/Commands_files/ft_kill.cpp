/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:02:50 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 16:58:43 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

// Command: KILL
//    Parameters: <nickname> <comment>

void kill(Cmd &command)
{
	User								*user;
	std::map<std::string, Channel *>	*chans;

	if (command.get_size() == 2)
	{
		if (command._user->get_mod().find("o") != std::string::npos)
		{
			if ((user = command._server->get_user(command.get_value()[0])) != NULL)
			{
				chans = command._server->get_chans();
				for (std::map<std::string, Channel *>::iterator it = chans->begin(); it != chans->end(); it++)
				{
					if (it->second->get_user(user->get_nick()))
						it->second->remove_user(user);
				}
				close(user->get_sfd());	
				command._server->remove_user(user);
				delete (user);
			}
			else
				command._server->send_msg(ERR_NOSUCHNICK(command._user->get_hostname(), command.get_value()[0], ""), command._sfd);
		}
		else
			command._server->send_msg(ERR_NOPRIVILEGES(command._user->get_hostname()), command._sfd);
	}
	else
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
}