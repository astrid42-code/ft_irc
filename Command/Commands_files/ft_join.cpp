/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:28:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/08/30 17:07:11 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

// Paramètres : <nom du chan> [<clé>]
// Réponses possibles : ERR_NEEDMOREPARAMS (461), ERR_BANNEDFROMCHAN (474), ERR_INVITEONLYCHAN (473), ERR_BADCHANNELKEY (475), ERR_CHANNELISFULL (471), ERR_NOSUCHCHANNEL (403), RPL_TOPIC (332)

// Ce message permet d'entrer sur un chan. Une fois qu'un utilisateur est sur un chan, il reçoit tous les messages (discussion et gestion) concernant ce chan. Si l'entrée est validée, le serveur transmet le message aux autres serveurs et autres utilisateurs présents sur le chan, puis le message RPL_TOPIC rappelle le topic du chan, et est suivi de messages RPL_NAMREPLY (353) avec la liste des nicks présents sur le chan, et enfin par un RPL_ENDOFNAMES (366). 

// command: JOIN
//    Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
//                / "0"

//    The JOIN command is used by a user to request to start listening to
//    the specific channel.  Servers MUST be able to parse arguments in the
//    form of a list of target, but SHOULD NOT use lists when sending JOIN
//    messages to clients.

//    Once a user has joined a channel, he receives information about
//    all commands his server receives affecting the channel.  This
//    includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
//    This allows channel members to keep track of the other channel
//    members, as well as channel modes.

//    If a JOIN is successful, the user receives a JOIN message as
//    confirmation and is then sent the channel's topic (using RPL_TOPIC) and
//    the list of users who are on the channel (using RPL_NAMREPLY), which
//    MUST include the user joining.

//    Note that this message accepts a special argument ("0"), which is
//    a special request to leave all channels the user is currently a member
//    of.  The server will process this message as if the user had sent
//    a PART command (See Section 3.2.2) for each channel he is a member
//    of.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//            ERR_CHANNELISFULL               ERR_BADCHANMASK
//            ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//            ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
//            RPL_TOPIC

//    Examples:

//    JOIN #foobar                    ; Command to join channel #foobar.

//    JOIN &foo fubar                 ; Command to join channel &foo using
//                                    key "fubar".

//    JOIN #foo,&bar fubar            ; Command to join channel #foo using
//                                    key "fubar" and &bar using no key.

//    JOIN #foo,#bar fubar,foobar     ; Command to join channel #foo using
//                                    key "fubar", and channel #bar using
//                                    key "foobar".

//    JOIN #foo,#bar                  ; Command to join channels #foo and
//                                    #bar.

//    JOIN 0                          ; Leave all currently joined
//                                    channels.

//    :WiZ!jto@tolsun.oulu.fi JOIN #Twilight_zone ; JOIN message from WiZ
//                                    on channel #Twilight_zone

void join(Cmd::Command & command){
    (void)command;
    std::cout << "join test" << '\n';
}