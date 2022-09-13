/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_user.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:18:44 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/11 16:10:37 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


// Command: USER
//    Parameters: <user> <mode> <unused> <realname>

//    The USER command is used at the beginning of connection to specify
//    the username, hostname and realname of a new user.

//    The <mode> parameter should be a numeric, and can be used to
//    automatically set user modes when registering with the server.  This
//    parameter is a bitmask, with only 2 bits having any signification: if
//    the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
//    set, the user mode 'i' will be set.  (See Section 3.1.5 "User
//    Modes").

//    The <realname> may contain space characters.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

//    Example:

//    USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
//                                    username of "guest" and real name
//                                    "Ronnie Reagan".

//    USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
//                                    username of "guest" and real name
//                                    "Ronnie Reagan", and asking to be set
//                                    invisible.

void user(Cmd &command)
{
	std::vector<std::string>::iterator it;

	printf("ft_user\n");
	command._user = new User();
	// init_user(command._user);
	std::cout << "command value size = " << command.get_value().size() << std::endl;
    if (command.get_value().size() != 4)
	{
		command._server->get_msg(ERR_NEEDMOREPARAMS(command.get_key()), NULL, command); 
	}
	std::cout << "setting the user" << std::endl;
	command._user->set_nick(command.get_value()[0]);
	command._user->set_user(command.get_value()[1]);
	command._user->set_host(command.get_value()[2]);
	command._user->set_name(command.get_value()[3]);
	command._user->set_operator(0);
	command._user->set_mod("");
	command._user->set_pwd("");
	// std::cout << command._user->get_name() << std::endl;
	// if (command.get_value()[0] == command._user->get_name()) // value[0] etant le login (get_name())
	// {
	// 	return;
	// }
	command._server->get_msg("RPL_WELCOME", command._user, command);
	command._server->get_msg("RPL_YOURHOST", command._user, command);
	command._server->get_msg("RPL_CREATED", command._user, command);
	command._server->get_msg("RPL_MYINFO", command._user, command);
}