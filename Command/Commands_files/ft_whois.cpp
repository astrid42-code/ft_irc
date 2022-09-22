/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whois.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:04:08 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/11 12:36:09 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


// Message WHOIS
// Paramètres : <nick>
// Réponses possibles : ERR_NONICKNAMEGIVEN (431), RPL_WHOISUSER (311), RPL_WHOISSERVER (312), RPL_WHOISOPERATOR (313), RPL_WHOISIDLE (317), RPL_ENDOFWHOIS (318), RPL_WHOISCHANNELS (319)

// Ce message permet de demander des informations sur un utilisateur telles que son masque (nick, nom et domaine de connexion), les chans où il est (et son statut sur ces chans), s'il a le statut d'IRCOP, etc.


//       Command: WHOIS
//    Parameters: [ <target> ] <mask> *( "," <mask> )

//    This command is used to query information about particular user.
//    The server will answer this command with several numeric messages
//    indicating different statuses of each user which matches the mask (if
//    you are entitled to see them).  If no wildcard is present in the
//    <mask>, any information about that nick which you are allowed to see
//    is presented.

//    If the <target> parameter is specified, it sends the query to a
//    specific server.  It is useful if you want to know how long the user
//    in question has been idle as only local server (i.e., the server the
//    user is directly connected to) knows that information, while
//    everything else is globally known.

//    Wildcards are allowed in the <target> parameter.

//    Numeric Replies:

//				ERR_NOSUCHSERVER				ERR_NONICKNAMEGIVEN
//				ERR_NOSUCHNICK
//				RPL_WHOISUSER
//				RPL_WHOISCHANNELS				RPL_WHOISSERVER
//				RPL_AWAY						RPL_WHOISOPERATOR
//				RPL_WHOISIDLE					RPL_ENDOFWHOIS

//    Examples:

//    WHOIS wiz                       ; return available user information
//                                    about nick WiZ

//    WHOIS eff.org trillian          ; ask server eff.org for user
//                                    information  about trillian
								   
void	whois(Cmd &command)
{
	bool					user_found = false;
	User					*user = NULL;
	std::map<int, User *>	users = command._server->get_users();

	std::cout << "whois test" << std::endl;
	if (command.get_size() == 1)
	{
		if (command.get_value()[0].find("*") != std::string::npos)
		{
			// for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
			// {
			// 	if (it->second->find_mod("i") == std::string::npos && mask_off(command.get_value()[0], it->second->get_hostname()))
			// 	{
					
			// 	}
			// }
		}
		else
		{
			if ((user = command._server->get_user(command.get_value()[0])) != NULL)
			{
				if (!user->find_mod("i"))
				{
					command._server->send_msg(RPL_WHOISUSER(user->get_nick(), user->get_user(), user->get_host(), user->get_name()), command);
					if (user->find_mod("o"))
						command._server->send_msg(RPL_WHOISOPERATOR(user->get_nick()), command);
					if (user->find_mod("a"))
						command._server->send_msg(RPL_AWAY(user->get_nick()), command);
					command._server->send_msg(RPL_ENDOFWHOIS(command._user->get_nick()), command);
				}
			}
			else
				command._server->send_msg(ERR_NOSUCHNICK(command.get_value()[0]), command);
		}
	}
	else if (command.get_size() == 2)
		command._server->send_msg(ERR_NOSUCHSERVER(command.get_value()[0]), command);
	else
		command._server->send_msg(ERR_NONICKNAMEGIVEN, command);
}