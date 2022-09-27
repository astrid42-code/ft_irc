/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whois.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:04:08 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/26 10:33:03 by asgaulti         ###   ########.fr       */
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
	bool						user_found = false;
	User						*user = NULL;
	std::map<int, User *>		users = command._server->get_users();
	std::vector<std::string>	args;

	std::cout << "whois test" << std::endl;
	if (command.get_size() == 1)
	{
		args = div_string(command.get_value()[0], ',');
		for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
		{
			if (it->find("*") != std::string::npos)
			{
				for (std::map<int, User *>::iterator at = users.begin(); at != users.end(); at++)
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
					std::cout << "user found :" << user->get_nick() << std::endl;
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
				{
					std::cout << "user not found :" << std::endl;
					command._server->send_msg(ERR_NOSUCHNICK(command._user->get_hostname(), *it), command._sfd);
				}
			}
		}
	}
	else if (command.get_size() == 2)
		command._server->send_msg(ERR_NOSUCHSERVER(command._user->get_hostname()), command._sfd);
	else
		command._server->send_msg(ERR_NONICKNAMEGIVEN(command._user->get_hostname()), command._sfd);
	if (user_found)
		command._server->send_msg(RPL_ENDOFWHOIS(command._user->get_hostname(), command._user->get_nick()), command._sfd);
}