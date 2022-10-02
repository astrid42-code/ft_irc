/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:02:15 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:12:25 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


// Command: QUIT
//    Parameters: [ <Quit Message> ]

void quit(Cmd &command)
{
	std::string									msg = "";
	std::map<std::string, Channel *>			*chans = command._server->get_chans();

	if (!chans->empty())
	{
		if (command.get_size() == 1)
			msg = command.get_value()[0];
		for (std::map<std::string, Channel *>::iterator	it = chans->begin(); it != chans->end(); it++)
		{
			if (erase_chan(it->second, command._user))
			{
				Channel *tmp = it->second;

				chans->erase(it);
				delete (tmp);
				it = chans->begin();
			}
			else
				it->second->send_to_users(QUIT(command._user->get_hostname(), msg));
		}
		// command._server->send_msg(QUIT(command._user->get_hostname(), msg), command._sfd);
		command._server->remove_user(command._user);
	}
	close(command._user->get_sfd());
	delete command._user;
}