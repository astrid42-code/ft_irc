/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invite.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:55:49 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/22 16:30:21 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


// Message INVITE
// Paramètres : <nick> <nom du chan>
// Réponses possibles : ERR_NEEDMOREPARAMS (461), ERR_NOSUCHNICK (401), ERR_NOTONCHANNEL (442), ERR_USERONCHANNEL (443), ERR_CHANOPRIVSNEEDED (482), RPL_INVITING(341)

// Permet d'inviter un utilisateur sur un chan. 


//       Command: INVITE
//    Parameters: <nickname> <channel>

//    The INVITE command is used to invite a user to a channel.  The
//    parameter <nickname> is the nickname of the person to be invited to
//    the target channel <channel>.  There is no requirement that the
//    channel the target user is being invited to must exist or be a valid
//    channel.  However, if the channel exists, only members of the channel
//    are allowed to invite other users.  When the channel has invite-only
//    flag set, only channel operators may issue INVITE command.

//    Only the user inviting and the user being invited will receive
//    notification of the invitation.  Other channel members are not
//    notified.  (This is unlike the MODE changes, and is occasionally the
//    source of trouble for users.)

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
//            ERR_NOTONCHANNEL                ERR_USERONCHANNEL
//            ERR_CHANOPRIVSNEEDED
//            RPL_INVITING                    RPL_AWAY

//    Examples:

//    :Angel!wings@irc.org INVITE Wiz #Dust

//                                    ; Message to WiZ when he has been
//                                    invited by user Angel to channel
//                                    #Dust

//    INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
//                                    #Twilight_zone

void invite(Cmd &command){
    // (void)command;
    std::cout << "invite test" << '\n';
    if (command.get_value().size() != 2){
        std::cout << "hello1" << std::endl;
        command._server->send_msg(461, ERR_NEEDMOREPARAMS(command.get_key()), command);
    }
    else if (command.get_value()[0] != command._user->get_name()){
		std::cout << "hello2" << std::endl;
        command._server->send_msg(401, ERR_NOSUCHNICK(command.get_value()[0]), command);
    }
    else if (command._user->get_mod() == "a"){ // ou faire une recherche de la lettre a car plsrs lettres possibles?
        std::cout << "hello3" << std::endl;
        command._server->send_msg(301, RPL_AWAY(command._user->get_nick()), command);
    }
    // if (command._user->isonchan(chan_name) == 0)
    //     command._server->send_msg(ERR_NOTONCHANNEL(chan_name), NULL);
    
    // si tout ok :
    // channel.invite(command._user->get_name()) > fct a faire dans la class channel pour connecter un user a un chan
    command._server->send_msg(341, RPL_INVITING(command.get_value()[0], command.get_value()[1]), command);
    // arg RPL_inviting : channel puis user
    
}