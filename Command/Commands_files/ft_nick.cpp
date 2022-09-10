/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:56:57 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/10 17:47:09 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


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

void nick(Cmd command)
{
    std::cout << "nick test " << std::endl;
    std::cout << command.get_size() << std::endl;
    if (!command.get_size())
    {
        std::cout << "Your nickname is " << DEFAULT_NAME << '\n'; // en attendant de recuperer le ptr sur user
        // a tester quand class user terminee
        command._user->set_user(DEFAULT_NAME);
        std::cout << "Your nickname is" << command._user->get_user() << '\n';
        return;
    }//  a tester quand class user terminee
    else
    {
            std::cout << "prout2 " << command.get_value()[0] << '\n';
            
            // command._user->set_nick(command._value[0]);
            std::cout << command._user->get_user() << '\n';
            // attention : tester avec ou sans la casse
        if (command.get_value()[0] != command._user->get_user()){
            std::cout << "You're now known as " << command.get_value()[0] << '\n';
        }
        else if (command.get_value()[0] == command._user->get_user()){
            command._server->get_msg(ERR_NICKNAMEINUSE(command.get_value()[0]), NULL); 
        }
    }
    
    //         else if (si chgmt de nick dans un autre serveur et nouveau nick deja enregistre)
    //          envoyer cmd kill > a ne pas faire (youpi)
    //         + ERR_NICKCOLLISION pour que client(l'utilisateur?) deconnecte les 2 clients
    //          https://mathieu-lemoine.developpez.com/tutoriels/irc/protocole/?page=page-3
    // // } 
}

// test :
// - /nick renvoie Your nickname is [nick]
// - /nick [nouveau nickname] renvoie "You're now known as [nouveau nick]"
// // penser a recuperer le nouveau nom de user et a le changer dans les infos du user actuel
// - /nick [meme nickname] renvoie "Nick [nick] is already in use" (err 433)