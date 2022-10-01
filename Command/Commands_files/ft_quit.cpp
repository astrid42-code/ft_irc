/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:02:15 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/30 13:46:27 by asgaulti         ###   ########.fr       */
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
	User										*user = command._user;
	std::string									msg = "";
	std::map<std::string, Channel *>			*chans = command._server->get_chans();
	std::map<std::string, Channel *>::iterator	it;
	int sfd;

	sfd = user->get_sfd();
	std::cout << "quit test" << std::endl;
	if (!chans->empty())
	{
		it = chans->begin();
		if (command.get_size() == 1)
		{
			msg = command.get_value()[0];
			std::cout << "quit msg " << msg << std::endl;
		}
		while (it != chans->end())
		{
			if (erase_chan(it->second, user))
			{
				Channel *tmp = it->second;

				chans->erase(it);
				std::cout << "elem erased" << std::endl;// effacer la cle du channel
				delete (tmp);
				std::cout << "elem deleted" << std::endl;// effacer la cle du channel
				it = chans->begin();
			}
			else
			{
				it->second->send_to_users(QUIT(user->get_hostname(), msg));
				it++;
			}
		}
	}
	command._server->send_msg(QUIT(user->get_hostname(), msg), command._sfd);
	command._server->remove_user(user);
	close(command._user->get_sfd());
	delete user;
}