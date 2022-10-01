/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_names.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:58:21 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:03:50 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

//       Command: NAMES
//    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

void names(Cmd &command)
{
	bool	verif = false;

	if (command.get_size() == 1)
	{
		Channel *chan;

		if ((chan = command._server->get_chan(command.get_value()[0])) != NULL)
		{
			std::map<int, User *> users = chan->get_users();

			if (!users.empty())
			{
				for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
				{
					if (!it->second->find_mod("i"))
					{
						verif = true;
						command._server->send_msg(RPL_NAMREPLY(command._user->get_hostname(), chan->get_name(), it->second->get_nick()), command._sfd);
					}
				}
			}
		}
	}
	else if (command.get_size() == 2)
		command._server->send_msg(ERR_NOSUCHSERVER(command._user->get_hostname(), command.get_value()[1]), command._sfd);
	else
	{
		std::map<int, User *> *users = command._server->get_users();

		for (std::map<int, User *>::iterator it = users->begin(); it != users->end(); it++)
		{
			if (!it->second->find_mod("i"))
			{
				verif = true;
				command._server->send_msg(RPL_NAMREPLY(command._user->get_hostname(), "*", it->second->get_nick()), command._sfd);
			}
		}
	}
	if (verif == true)
					command._server->send_msg(RPL_ENDOFNAMES(command._user->get_hostname(), command._user->get_user(), "*"), command._sfd);
}