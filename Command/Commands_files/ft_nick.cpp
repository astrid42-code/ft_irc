/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:56:57 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/22 16:45:38 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../Server/Server.hpp"


// Command: NICK
//    Parameters: <nickname>

//    NICK command is used to give user a nickname or change the existing
//    one.
//    Numeric Replies:

//            ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//            ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
//            ERR_UNAVAILRESOURCE             ERR_RESTRICTED

//    Examples:

//    NICK Wiz                ; Introducing new nick "Wiz" if session is
//                            still unregistered, or user changing his
//                            nickname to "Wiz"

//    :WiZ!jto@tolsun.oulu.fi NICK Kilroy
//                            ; Server telling that WiZ changed his
//                            nickname to Kilroy.

void nick(Cmd &command)
{
	std::cout << "ft_nick" << std::endl;
	if (command.get_size() == 0)
	{
		std::cout << "no nickname given." << std::endl;
		command._server->send_msg(ERR_NONICKNAMEGIVEN(command._user->get_hostname()), command._sfd);
	}
	else
	{
		if (command._server->get_user(command.get_value()[0]) == NULL && command.get_value()[0].compare("anonymous") != 0)
		{
			std::cout << "nickname available." << std::endl;
			command._user->set_nick(command.get_value()[0]);
			if (command._user->get_valid() == 1)
				command._user->set_valid(2);
			else
				command._server->send_msg(NICK(command._user->get_hostname(), command._user->get_nick()), command._sfd);
		}
		else
		{
			std::cout << "nickname already in use." << std::endl;
			command._server->send_msg(ERR_NICKNAMEINUSE(command._user->get_hostname(), command.get_value()[0]), command._sfd);
		}
		// attention : tester avec ou sans la casse		
	}
	// std::cout << "endofnickname" << std::endl;
}

// test :
// - /nick renvoie Your nickname is [nick]
// - /nick [nouveau nickname] renvoie "You're now known as [nouveau nick]"
// // penser a recuperer le nouveau nom de user et a le changer dans les infos du user actuel
// - /nick [meme nickname] renvoie "Nick [nick] is already in use" (err 433), 