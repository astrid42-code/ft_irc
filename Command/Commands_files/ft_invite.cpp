/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invite.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:55:49 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 16:55:55 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

// Message INVITE
// Paramètres : <nick> <nom du chan>

void invite(Cmd &command)
{
	User	*user;
	Channel	*chan;

    if (command.get_value().size() != 2)
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
	else
	{
		if (!(user = command._server->get_user(command.get_value()[0])))
			command._server->send_msg(ERR_NOSUCHNICK(command._user->get_hostname(), command.get_value()[0], command.get_value()[1]), command._sfd);
		else
		{
			if (user->find_mod("a"))
				command._server->send_msg(RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), command._user->get_away()), command._sfd);
			else
			{
				if (user->get_channel(command.get_value()[1]))
					command._server->send_msg(ERR_USERONCHANNEL(command._user->get_hostname(), command.get_value()[0], command.get_value()[1]), command._sfd);
				else
				{
					if (!(chan = command._user->get_channel(command.get_value()[1])))
						command._server->send_msg(ERR_NOTONCHANNEL(command._user->get_hostname(), command.get_value()[1]), command._sfd);
					else
					{
						if (chan->get_mod().find('i') && (!command._user->find_mod("o") && !command._user->find_mod("O")))
								command._server->send_msg(ERR_CHANOPRIVSNEEDED(command._user->get_hostname(), command.get_value()[1]), command._sfd);
						else
						{
							command._server->send_msg(RPL_INVITING(command._user->get_hostname(), command.get_value()[1], command.get_value()[0]), command._sfd); // nick de l'invitant ou de l'invite???
							command._server->send_msg(RPL_INVITING(command._user->get_hostname(), command.get_value()[1], command.get_value()[0]), command._server->get_user(command.get_value()[0])->get_sfd());
						}
					}
				}
			}
		}
	}
}
