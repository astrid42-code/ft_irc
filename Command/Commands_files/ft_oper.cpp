/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oper.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:00:36 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/26 16:26:15 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


//  Command: OPER
//    Parameters: <name> <password>

//    A normal user uses the OPER command to obtain operator privileges.
//    The combination of <name> and <password> are REQUIRED to gain
//    Operator privileges.  Upon success, the user will receive a MODE
//    message (see section 3.1.5) indicating the new user modes.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              RPL_YOUREOPER
//            ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

//    Example:

//    OPER foo bar                    ; Attempt to register as an operator
//                                    using a username of "foo" and "bar"
//                                    as the password.


void oper(Cmd &command)
{
	std::cout << "oper test" << std::endl;
		std::cout << "|" << command.get_value()[0] << "| |" << command.get_value()[1] << "|" << std::endl;
	if (command.get_size() != 2)
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
	if (command._server->get_pwd() != command.get_value()[1]){
		std::cout << "pas lol" << std::endl;
		command._server->send_msg(ERR_PASSWDMISMATCH(command._user->get_hostname(), command._user->get_nick()), command._sfd);
	}
	else{
		if (command._user->find_mod("o") == 1)
			return;
		command._user->set_mod(command._user->get_mod() + "o");
		command._server->send_msg(RPL_YOUREOPER(command._user->get_hostname()), command._sfd);
	}
}