/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:31:20 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/11 14:21:22 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../RPL_answer.hpp"

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


void pass(Cmd &command){
    std::cout << "pass test " << command.get_key() << '\n';
    if (command.get_value().size() != 1){
        command._server->get_msg(ERR_NEEDMOREPARAMS(command.get_key()), command._user, command);
        return;
    }
    if (command.get_value()[0] == command._user->get_name()){// value[0] etant le login (get_name())
		command._server->get_msg(ERR_ALREADYREGISTRED, NULL, command);
	}
        return;
}