/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:38:02 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:00:27 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


// Message LIST
// Paramètres : [<nom du chan>]

void list(Cmd &command)
{
	if (command.get_size() == 0)
	{
		std::map<std::string, Channel *>	*chans = command._server->get_chans();

		for (std::map<std::string, Channel *>::iterator it = chans->begin(); it != chans->end(); it++)
		{
			if (it->second->get_mod().find('s') == std::string::npos && it->second->get_mod().find('p') == std::string::npos)
				command._server->send_msg(RPL_LIST(command._user->get_hostname(), it->first, it->second->get_mod(), it->second->get_topic()), command._sfd);
		}
		command._server->send_msg(RPL_LISTEND(command._user->get_hostname()), command._sfd);
	}
	else if (command.get_size() == 1)
	{
		Channel 					*chan;
		std::vector<std::string>	chans = div_string(command.get_value()[0], ',');

		for (size_t i = 0; i < chans.size(); i++)
		{
			if ((chan = command._server->get_chan(chans[i])) != NULL)
			{
				if (chan->get_mod().find('s') == std::string::npos && chan->get_mod().find('p') == std::string::npos)
					command._server->send_msg(RPL_LIST(command._user->get_hostname(), chan->get_name(), chan->get_mod(), chan->get_topic()), command._sfd);
			}
		}
		command._server->send_msg(RPL_LISTEND(command._user->get_hostname()), command._sfd);
	}
	else if (command.get_size() > 1)
		command._server->send_msg(ERR_NOSUCHSERVER(command._user->get_hostname(), command.get_value()[1]), command._sfd);
}