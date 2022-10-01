/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_privmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:17 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:11:39 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


//       Command: PRIVMSG
//    Parameters: <msgtarget> <text to be sent>

void send_msg_to_user(User *usr, std::string str, Cmd &command, std::string chan)
{
	if (usr->find_mod("a")){
		command._server->send_msg(RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), command._user->get_away()), command._sfd);
		return;
	}
	else{
		command._server->send_msg(PRIVMSG(command._user->get_hostname(), chan, str), usr->get_sfd());
		return;
	}
}

void send_msg_to_chan(Cmd &command, std::string destinataire)
{
	Channel *chan;
	std::map<int, User *>::iterator it;
	std::map<int, User *> users;

	chan = command._server->get_chan(destinataire.c_str());
	if (!chan || !chan->get_user(command._user->get_nick())){
		command._server->send_msg(ERR_CANNOTSENDTOCHAN(command._user->get_hostname(), command._user->get_nick(), destinataire), command._sfd);
		return;
	}
	else
	{
		users = chan->get_users();
		it = users.begin();
		while (it != users.end())
		{
			if (command._user != it->second)
				send_msg_to_user(it->second, command.get_value()[1], command, destinataire);
			it++;
		}
	}
}

void privmsg(Cmd &command)
{
	User *user;
	std::string destinataire;

	if (command.get_size() < 1)
		command._server->send_msg(ERR_NORECIPIENT(command._user->get_hostname()), command._sfd);
	else
	{
		destinataire = command.get_value().begin()[0];
		if (command.get_size() == 1 || (command.get_size() == 2 && command.get_value()[1].empty()))
			command._server->send_msg(ERR_NOTEXTTOSEND(command._user->get_hostname()), command._sfd);
		else
		{
			if (destinataire.c_str()[0] == '#')
				send_msg_to_chan(command, destinataire);
			else
			{
				if ((user = command._server->get_user(destinataire)) != NULL)
				{
					if (user->find_mod("a"))
						command._server->send_msg(RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), command._user->get_away()), command._sfd);
					else
						command._server->send_msg(PRIVMSG(command._user->get_hostname(), destinataire,command.get_value()[1]),command._server->get_user(destinataire)->get_sfd());
				}
				else
					command._server->send_msg(ERR_NOSUCHNICK(command._user->get_hostname(), destinataire, ""), command._sfd);
			}
		}
	}
}