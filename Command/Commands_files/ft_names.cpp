/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_names.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:58:21 by asgaulti          #+#    #+#             */
/*   Updated: 2022/08/29 16:23:39 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

// Paramètres : <nom du chan>
// Réponses possibles : RPL_NAMREPLY (353), RPL_ENDOFNAMES (366)

// Permet de redemander la liste des personnes présentes sur le chan et leur statut (op, voice, simple membre). 

//       Command: NAMES
//    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

//    By using the NAMES command, a user can list all nicknames that are
//    visible to him. For more details on what is visible and what is not,
//    see "Internet Relay Chat: Channel Management" [IRC-CHAN].  The
//    <channel> parameter specifies which channel(s) to return information
//    about.  There is no error reply for bad channel names.

//    If no <channel> parameter is given, a list of all channels and their
//    occupants is returned.  At the end of this list, a list of users who
//    are visible but either not on any channel or not on a visible channel
//    are listed as being on `channel' "*".

//    If the <target> parameter is specified, the request is forwarded to
//    that server which will generate the reply.

//    Wildcards are allowed in the <target> parameter.

//    Numerics:

//            ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
//            RPL_NAMREPLY                    RPL_ENDOFNAMES

//    NAMES #twilight_zone,#42        ; Command to list visible users on
//                                    #twilight_zone and #42

//    NAMES                           ; Command to list all visible
//                                    channels and users

void names(Cmd::Command & command){
    std::cout << "name test" << '\n';
}