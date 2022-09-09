/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whois.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:04:08 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/09 16:53:59 by asgaulti         ###   ########.fr       */
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

//            ERR_NOSUCHSERVER              ERR_NONICKNAMEGIVEN
//            RPL_WHOISUSER                 RPL_WHOISCHANNELS
//            RPL_WHOISCHANNELS             RPL_WHOISSERVER
//            RPL_AWAY                      RPL_WHOISOPERATOR
//            RPL_WHOISIDLE                 ERR_NOSUCHNICK
//            RPL_ENDOFWHOIS
//    Examples:

//    WHOIS wiz                       ; return available user information
//                                    about nick WiZ

//    WHOIS eff.org trillian          ; ask server eff.org for user
//                                    information  about trillian
                                   
void whois(Cmd command){
    (void)command;
    std::cout << "whois test" << '\n';
}