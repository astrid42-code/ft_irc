/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:56:57 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/06 11:18:37 by asgaulti         ###   ########.fr       */
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

void nick(Cmd::Command & command){
    std::cout << "nick test" << '\n';
    if (command._value.size() == 0){
        std::cout << "blabla" << '\n';
        // std::cout << "Your nickname is" << command._user.getName() << '\n';
        return;
    }
    std::cout << "lol" << '\n';
    // else {
    //     if (command._value[0] != command._user.getName()){
    //         // std::cout << "You're now known as " << command._value[0] << '\n';
    //     }
    //     else if (command._value[0] == command._user.getName()){
    //         server.get_msg(ERR_NICKNAMEINUSE(command._value[0])); 
    //     }
    // } 
}

// test :
// - /nick renvoie Your nickname is [nick]
// - /nick [nouveau nickname] renvoie "You're now known as [nouveau nick]"
// - /nick [meme nickname] renvoie "Nick [nick] is already in use" (err 433)