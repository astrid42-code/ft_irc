/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:02:15 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/22 16:50:29 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


// Command: QUIT
//    Parameters: [ <Quit Message> ]

//    A client session is terminated with a quit message.  The server
//    acknowledges this by sending an ERROR message to the client.

//    Numeric Replies:

//            None.

//    Example:

//    QUIT :Gone to have lunch        ; Preferred message format.

//    :syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch ; User
//                                    syrk has quit IRC to have lunch.


void quit(Cmd &command)
{
	User *tmp;

	if (command.get_size() == 1)
	{
		std::vector<Channel *>	chans = command._user->get_chans();

		std::cout << "quit msg " << command.get_value()[0] << std::endl;
		for (std::vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
			(*it)->send_to_users(":" + command._user->get_hostname() + " QUIT :" + command.get_value()[0]);
	}
	command._server->send_msg("ERROR\r\n", command._sfd);
	close(command._sfd); //... j'arrive pas a forcer le client a fermer sa connection (try avec nc)
	tmp = command._user;
	command._server->remove_user(command._user);
	delete tmp;
}