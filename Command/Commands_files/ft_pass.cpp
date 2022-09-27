/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:31:20 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/27 18:04:41 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../RPL_answer.hpp"

// The commands described here are used to register a connection with an
//    IRC server as a user as well as to correctly disconnect.

//    A "PASS" command is not required for a client connection to be
//    registered, but it MUST precede the latter of the NICK/USER
//    combination (for a user connection) or the SERVICE command (for a
//    service connection). The RECOMMENDED order for a client to register
//    is as follows:

//                            1. Pass message
//            2. Nick message                 2. Service message
//            3. User message

//    Upon success, the client will receive an RPL_WELCOME (for users) or
//    RPL_YOURESERVICE (for services) message indicating that the
//    connection is now registered and known the to the entire IRC network.
//    The reply message MUST contain the full client identifier upon which
//    it was registered.


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
    // std::cout << "pass test " << std::endl;
    if (command.get_value().size() != 1)
	{
        command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
        return;
    }
    if (!command._server->get_pwd().empty()) // si on n'a pas le droit de changer le pwd (sinon je sais pas quel type d'erreru c ca)
	{
		command._server->send_msg(ERR_ALREADYREGISTRED(command._user->get_hostname()), command._sfd);
		return;
	}
	else if (command._user->get_pwd().empty())
		command._server->set_pwd(command.get_value()[0]);


}

// a verifier : pour le pwd server ou / et user?