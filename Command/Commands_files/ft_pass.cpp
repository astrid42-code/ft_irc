/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:31:20 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/26 10:02:13 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
// #include "../../RPL_answer.hpp"
#include "../../RPL_answer2.hpp"

// Command: PASS
//    Parameters: <password>

//    The PASS command is used to set a 'connection password'.  The
//    optional password can and MUST be set before any attempt to register
//    the connection is made. Currently this requires that user send a
//    PASS command before sending the NICK/USER combination.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS (461)              ERR_ALREADYREGISTRED (462)

//    Example:

//            PASS secretpasswordhere


void pass(Cmd &command)
{
    std::cout << "pass test " << command.get_key() << std::endl;
    if (command.get_value().size() != 1)
	{
        command._server->send_msg(461, ERR_NEEDMOREPARAMS(command.get_key()), command);
        return;
    }
    if (command.get_value()[0] == command._user->get_name())
	{// value[0] etant le login (get_name())
		command._server->send_msg(462, ERR_ALREADYREGISTRED, command);
	}
	if (command.get_value()[0] == command._user->get_name())
	{// value[0] etant le login (get_name())
		command._server->send_msg(462, ERR_ALREADYREGISTRED, command);
	}
		return;
}