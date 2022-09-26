/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_away.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:30:27 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/26 12:12:30 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
// #include "../../RPL_answer.hpp"
#include "../../RPL_answer2.hpp"
#include "../../Server/Server.hpp"

// Command: AWAY
//    Parameters: [ <text> ]

//    With the AWAY command, clients can set an automatic reply string for
//    any PRIVMSG commands directed at them (not to a channel they are on).
//    The server sends an automatic reply to the client sending the PRIVMSG
//    command.  The only replying server is the one to which the sending
//    client is connected to.

//    The AWAY command is used either with one parameter, to set an AWAY
//    message, or with no parameters, to remove the AWAY message.

//    Because of its high cost (memory and bandwidth wise), the AWAY
//    message SHOULD only be used for client-server communication.  A
//    server MAY choose to silently ignore AWAY messages received from
//    other servers.  To update the away status of a client across servers,
//    the user mode 'a' SHOULD be used instead.  (See Section 3.1.5)

//    Numeric Replies:

//            RPL_UNAWAY                    RPL_NOWAWAY
//    Example:

//    AWAY :Gone to lunch.  Back in 5 ; Command to set away message to
//                                    "Gone to lunch.  Back in 5".


void	away(Cmd &command)
{
	std::string mod = command._user->get_mod();
	std::string msg;
	
	std::cout << "away msg1 " << command.get_value()[0] << std::endl;
	if (command.get_value()[0] == ""){
		msg = AWAY_DEFAULT;
	}
	else
		msg = command.get_value()[0];
	
	command._server->send_msg(301, RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), msg), command);
}