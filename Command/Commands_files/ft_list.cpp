/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:38:02 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/11 12:36:09 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


// Message LIST
// Paramètres : [<nom du chan>]
// Réponses possibles : RPL_LISTSTART (321) (obsolete, not used), RPL_LIST (322), RPL_LISTEND (323)

// Permet de demander la liste des chans, ou les détails sur un chan en particulier. 

//   Command: LIST
//    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

//    The list command is used to list channels and their topics.  If the
//    <channel> parameter is used, only the status of that channel is
//    displayed.

//    If the <target> parameter is specified, the request is forwarded to
//    that server which will generate the reply.

//    Wildcards are allowed in the <target> parameter.

//    Numeric Replies:

//            ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
//            RPL_LIST                        RPL_LISTEND

//    Examples:

//    LIST                            ; Command to list all channels.

//    LIST #twilight_zone,#42         ; Command to list channels
//                                    #twilight_zone and #42

void list(Cmd &command){
    (void)command;
    std::cout << "list test" << '\n';
    // tant que la liste de channels (separes par une ,) n est pas finie
    // verifier si le channel existe dans la map de channels (et si arg[1] rajouter le topic associe)
    
    
}