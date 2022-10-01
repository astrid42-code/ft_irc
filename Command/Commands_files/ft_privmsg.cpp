/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_privmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:17 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 12:16:37 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


//       Command: PRIVMSG
//    Parameters: <msgtarget> <text to be sent>

//    PRIVMSG is used to send private messages between users, as well as to
//    send messages to channels.  <msgtarget> is usually the nickname of
//    the recipient of the message, or a channel name.

//    The <msgtarget> parameter may also be a host mask (#<mask>) or server
//    mask ($<mask>).  In both cases the server will only send the PRIVMSG
//    to those who have a server or host matching the mask.  The mask MUST
//    have at least 1 (one) "." in it and no wildcards following the last
//    ".".  This requirement exists to prevent people sending messages to
//    "#*" or "$*", which would broadcast to all users.  Wildcards are the
//    '*' and '?'  characters.  This extension to the PRIVMSG command is
//    only available to operators.

//    Numeric Replies:

//            ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
//            ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
//            ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
//            ERR_NOSUCHNICK
//            RPL_AWAY

void send_msg_to_user(User *usr, std::string str, Cmd &command, std::string chan)
{
	if (usr->find_mod("a"))
		command._server->send_msg(RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), command._user->get_away()), command._sfd);
	else if (!usr->find_mod("i"))
		command._server->send_msg(PRIVMSG(command._user->get_hostname(), chan, str), usr->get_sfd());
}

void send_msg_to_chan(Cmd &command, std::string destinataire)
{
	Channel *chan;
	std::map<int, User *>::iterator it;
	std::map<int, User *> users;

	std::cout << "________msg_to_chan________" << std::endl;
	chan = command._server->get_chan(destinataire.c_str());
	if (!chan || !chan->get_user(command._user->get_nick()))
		command._server->send_msg(ERR_CANNOTSENDTOCHAN(command._user->get_hostname(), command._user->get_nick(), destinataire), command._sfd);
	else
	{
		users = chan->get_users();
		it = users.begin();
		while (it != users.end())
		{
			// std::cout << "User :" << command._user->get_nick() << std::endl;
			if (command._user != it->second)
				send_msg_to_user(it->second, command.get_value()[1], command, destinataire);
			it++;
		}
	}
	std::cout << "__________test__________" << std::endl;
}

void privmsg(Cmd &command)
{
	User *user;
	std::string destinataire;

	std::cout << "privmsg test" << std::endl;
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
			{
				// std::cout << "msg_to_chan" << std::endl;
				send_msg_to_chan(command, destinataire);
			}
			else
			{
				// std::cout << "msg_to_user" << std::endl;
				if ((user = command._server->get_user(destinataire)) != NULL)
				{
					if (user->find_mod("a"))
						command._server->send_msg(RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), command._user->get_away()), command._sfd);
					else if (!user->find_mod("i"))
						command._server->send_msg(PRIVMSG(command._user->get_hostname(), destinataire,command.get_value()[1]),command._server->get_user(destinataire)->get_sfd());
				}
				else
					command._server->send_msg(ERR_NOSUCHNICK(command._user->get_hostname(), destinataire), command._sfd);
			}
		}
	}
	// std::cout << "destinataire : |" << destinataire.c_str() << "|" << std::endl;
}