/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notice.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:04:30 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:05:37 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

//       Command: NOTICE
//    Parameters: <msgtarget> <text>


void send_msg_to_chan_not(Cmd &command, std::string destinataire)
{
	Channel *chan;
	std::map<int, User *>::iterator it;
	std::map<int, User *> users;

	chan = command._server->get_chan(destinataire.c_str());
	if (!chan || !chan->get_user(command._user->get_nick()))
		return;
	else
	{
		users = chan->get_users();
		it = users.begin();
		while (it != users.end())
		{
			if (command._user != it->second)
			{
				if (it->second->find_mod("a"))
					command._server->send_msg(RPL_AWAY(command._user->get_hostname(), it->second->get_nick(), command._user->get_away()), command._sfd);
				if (!it->second->find_mod("i"))
					command._server->send_msg(NOTICE(command._user->get_hostname(), chan->get_name(), command.get_value()[1]),command._server->get_user(destinataire)->get_sfd());
			}
			it++;
		}
	}
}

void	notice(Cmd &command)
{
	User		*user;
	std::string	destinataire;

	std::cout << "notice test" << std::endl;
	if (command.get_size() <= 1 || (command.get_size() == 2 && command.get_value()[1].empty()))
		return;
	destinataire = command.get_value().begin()[0];
	if (destinataire.c_str()[0] == '#')
		send_msg_to_chan_not(command, destinataire);
	else
	{
		if ((user = command._server->get_user(destinataire)) != NULL)
		{
			if (user->find_mod("a"))
				command._server->send_msg(RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), command._user->get_away()), command._sfd);
			if (!user->find_mod("i"))
				command._server->send_msg(NOTICE(command._user->get_hostname(), destinataire,command.get_value()[1]),command._server->get_user(destinataire)->get_sfd());

		}
	}
}
