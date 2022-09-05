/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:31:20 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/05 17:39:30 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

// Command: PASS
//    Parameters: <password>

//    The PASS command is used to set a 'connection password'.  The
//    optional password can and MUST be set before any attempt to register
//    the connection is made.  Currently this requires that user send a
//    PASS command before sending the NICK/USER combination.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS (461)              ERR_ALREADYREGISTRED (462)

//    Example:

//            PASS secretpasswordhere


void pass(Cmd::Command & command){
    std::cout << "pass test " << command._key << '\n';
    // if (command._value.size() != 1){
    //     server.get_msg = (ERR_NEEDMOREPARAMS(command._key)); 
    //  dans server : faire une fct qui recupere le define / le msg complet et qui l'imprime
    // }
    // if (command._value[0] == server.get_name()){// value[0] etant le login (get_name())
	// 		ERR_ALREADYREGISTRED + envoyer le get_name()
	// }
        
}