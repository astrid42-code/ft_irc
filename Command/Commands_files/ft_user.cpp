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
void	init_user(User *user)
{
	user->set_name("Tad amigo");
	user->set_mod("o");
	user->set_nick("tamigore");
	user->set_operator(1);
	user->set_pwd("1234567890");
	user->set_user("Tadeo");
}

void user(Cmd &command)
{
	printf("ft_user\n");
	command._user = new User();
	init_user(command._user);
	//std::cout << command.get_size() << std::endl;
	// for (int i = 0; i < command.get_size(); i++){
	// 	std::cout << "value" << i << " " << command.get_value()[i] << std::endl;
	// }
    // if (command.get_size() != 4){
    //     command._server->get_msg(ERR_NEEDMOREPARAMS(command.get_key()), NULL, command); 
	// }
	
	// set les valeurs du _user avec les args contenus dans _value
	//command._user->set_name(command.get_value()[0]); // segfault :( 
		// comment set les infos du _user ?
	// std::cout << command._user->get_name() << std::endl;
	// if (command.get_value()[0] == command._user->get_name())
	// {// value[0] etant le login (get_name())
	// 	return;
	// }
	command._server->get_msg("RPL_WELCOME", command._user, command);
}