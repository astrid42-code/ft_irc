/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_user.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:18:44 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/15 20:04:43 by asgaulti         ###   ########.fr       */
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
	if (command._user == NULL)
		command._user = new User();
    if (command.get_size() != 4)
	{
		std::cout << "error wrong number of params :" << command.get_size() << std::endl;
		command._server->get_msg(ERR_NEEDMOREPARAMS(command.get_key()), command._user, command);
		return ;
	}
	std::cout << "setting the user" << std::endl;
	if (command._server->get_user(command.get_value()[0]) == NULL)
	{
		command._user->set_nick(command.get_value()[0]);
		command._user->set_user(command.get_value()[1]);
		command._user->set_host(command.get_value()[2]);
		command._user->set_name(command.get_value()[3]);
		command._user->set_operator(0);
		command._user->set_mod("");
		command._user->set_pwd("");
		command._user->set_sfd(command._sfd);
	}
	else
	{
		std::cout << "nickname already in use." << std::endl;
		command._server->get_msg("ERR_NICKNAMEINUSE", command._user, command);
		return ;
	}
	command._server->get_msg("RPL_WELCOME", command._user, command);
	command._server->get_msg("RPL_YOURHOST", command._user, command);
	command._server->get_msg("RPL_CREATED", command._user, command);
	command._server->get_msg("RPL_MYINFO", command._user, command);
<<<<<<< HEAD
	command._server->set_user(*command._user);
	command._server->get_msg("RPL_MOTD", command._user, command);
	if (command._user)
		delete command._user;
=======
	command._server->set_user(command._user);
	// if (command._user)
	// 	delete command._user;
>>>>>>> 43e4d6bce943151af6d1d169636783987248d711
}