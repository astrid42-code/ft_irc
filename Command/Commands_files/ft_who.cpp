/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_who.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:42 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:13:49 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

//       Command: WHO
//    Parameters: [ <mask> [ "o" ] ]

void	who(Cmd &command)
{
	std::map<int, User *>	*users = command._server->get_users();
	std::vector<Channel *>	*chans = command._user->get_chans();
	bool					match = false;

	for (std::map<int, User *>::iterator itu = users->begin(); itu != users->end(); itu++)
	{
		if (itu->second && !itu->second->find_mod("i") && itu->second != command._user)
		{
			if (command.get_size() >= 1 && command.get_value()[0].compare("0") != 0 && command.get_value()[0].compare("*") != 0)
			{
				if (mask_off(command.get_value()[0], itu->second->get_hostname()) || mask_off(command.get_value()[0], itu->second->get_name())
					|| mask_off(command.get_value()[0], itu->second->get_nick()) || mask_off(command.get_value()[0], SERVER))
				{
					if (command.get_size() == 1 || (command.get_size() == 2 && command.get_value()[1].compare("o") == 0 && itu->second->find_mod("o")))
					{
						command._server->send_msg(RPL_WHOREPLY(command._user->get_hostname(), itu->second->get_channel_name(), itu->second->get_user(), itu->second->get_host(), itu->second->get_nick(), itu->second->get_name()), command._sfd);
						match = true;
					}
				}
			}
			else
			{
				for (std::vector<Channel *>::iterator itc = chans->begin(); itc != chans->end(); itc++)
				{
					if (!itu->second->find_mod("i"))
					{
						if (command.get_size() < 2 || (command.get_size() == 2 && command.get_value()[2][0] == 'o' && itu->second->find_mod("o")))
						{
							command._server->send_msg(RPL_WHOREPLY(command._user->get_hostname(), itu->second->get_channel_name(), itu->second->get_user(), itu->second->get_host(), itu->second->get_nick(), itu->second->get_name()), command._sfd);
							match = true;
						}
					}
				}
			}
		}
	}
	if (match == true)
		command._server->send_msg(RPL_ENDOFWHO(command._user->get_hostname(), command._server->get_ip()), command._sfd);
}