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
	User										*user = command._user;
	std::string									msg = "";
	std::map<std::string, Channel *>			*chans = command._server->get_chans();
	std::map<std::string, Channel *>::iterator	it;
	int sfd;

	sfd = user->get_sfd();
	if (!chans->empty())
	{
		it = chans->begin();
		if (command.get_size() == 1)
			msg = command.get_value()[0];
		while (it != chans->end())
		{
			if (erase_chan(it->second, user))
			{
				Channel *tmp = it->second;

				chans->erase(it);
				delete (tmp);
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