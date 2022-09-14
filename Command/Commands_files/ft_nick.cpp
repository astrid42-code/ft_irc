/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:56:57 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/14 15:25:15 by asgaulti         ###   ########.fr       */
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
		command._server->get_msg("ERR_NONICKNAMEGIVEN", command._user, command);
	}
	else
	{
			// std::cout << " coucou" << std::endl;
		if (command._server->get_user(command.get_value()[0]) == User())
		{
			if (command._user == NULL)
				command._user = new User();
			command._user->set_nick(command.get_value()[0]);
			command._user->set_sfd(command._sfd);
			command._server->set_user(*command._user);
			std::cout << command._server->get_user(command.get_value()[0]) << std::endl;
			std::string tmp = command.get_value()[0];
			if (command._user)
				delete command._user;
			std::cout << command._server->get_user(tmp) << std::endl;
		}
		else
		{
			std::cout << "nickname already in use." << std::endl;
			command._server->get_msg("ERR_NICKNAMEINUSE", command._user, command);
		}
		
		// attention : tester avec ou sans la casse
		// if (command.get_value()[0] != command._user->get_user()){
		// command._user->set_user(DEFAULT_NAME);
		// std::cout << "Your nickname is" << command._user->get_user() << std::endl;
		//necessite de nettoyer le vector _value a la fin de chaque cmd (ou tout simplement ~Cmd mais comment faire?)
		// }
		// else if (command.get_value()[0] == command._user->get_user()){
		//     command._server->get_msg(ERR_NICKNAMEINUSE(command.get_value()[0]), NULL);
		// }
	}
	// std::cout << "nickname :" << command._user->get_nick() << std::endl;
}

// test :
// - /nick renvoie Your nickname is [nick]
// - /nick [nouveau nickname] renvoie "You're now known as [nouveau nick]"
// // penser a recuperer le nouveau nom de user et a le changer dans les infos du user actuel
// - /nick [meme nickname] renvoie "Nick [nick] is already in use" (err 433)