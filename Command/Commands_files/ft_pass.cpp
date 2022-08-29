/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:31:20 by asgaulti          #+#    #+#             */
/*   Updated: 2022/08/29 16:12:12 by asgaulti         ###   ########.fr       */
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
    std::cout << "pass test" << '\n';
    // if (command._value.size() != 1){
    //     send(ERR_NEEDMOREPARAMS())
    // }
    // if (command._value[0] == server.get_pwd()){
	// 		send(ERR_ALREADYREGISTRED )
	// }
    
        
}