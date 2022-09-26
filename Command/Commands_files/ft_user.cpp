/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_user.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:18:44 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/26 10:00:34 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
// #include "../../Server/Server.hpp"


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
// (void)command;
	printf("ft_user\n");
    if (command.get_size() != 4)
	{
		std::cout << "error wrong number of params :" << command.get_size() << std::endl;
		command._server->send_msg(461, ERR_NEEDMOREPARAMS(command.get_key()), command);
		return ;
	}
	// std::cout << "setting the user" << std::endl;
	if (command.get_value()[1].compare("anonymous") == 0 || command.get_value()[2].compare("anonymous") == 0)
	{
		command._server->send_msg(462, ERR_ALREADYREGISTRED, command);
	}
	else
	{
		command._user->set_user(command.get_value()[1]);
		command._user->set_host(command.get_value()[2]);
	}
	command._user->set_name(command.get_value()[3]);
	command._user->set_operator(0);
	command._user->set_mod("");
	command._user->set_pwd("");
	command._user->set_sfd(command._sfd);
	command._server->set_user(command._user);
	// command._server->send_msg(375, "", command._user, command);
	// command._server->send_msg(376, "", command._user, command);

	// send_msg(375, command._user, command);
	// send_msg(376, command._user, command);
	
	// command._server->send_msg("RPL_WELCOME", command._user, command);
	// command._server->send_msg("RPL_YOURHOST", command._user, command);
	// command._server->send_msg("RPL_CREATED", command._user, command);
	// command._server->send_msg("RPL_MYINFO", command._user, command);
	// command._server->send_msg("RPL_MOTD", command._user, command);
	
	command._server->send_msg(1, RPL_WELCOME(command._user->get_hostname(), command._user->get_nick()), command);
	command._server->send_msg(2, RPL_YOURHOST, command);
	command._server->send_msg(3, RPL_CREATED, command);
	command._server->send_msg(4, RPL_MYINFO, command);
	command._server->send_msg(375, RPL_MOTDSTART, command);
	command._server->send_msg(0, RPL_MOTD(PINGU), command);
	command._server->send_msg(0, RPL_ENDOFMOTD, command);
}