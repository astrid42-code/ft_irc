/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_away.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:30:27 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 16:55:44 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../RPL_answer.hpp"

#include "../../Server/Server.hpp"

// Command: AWAY
//    Parameters: [ <text> ]

void	away(Cmd &command)
{
	std::string mod = command._user->get_mod();
	std::string msg;
	
	if (command.get_size() < 1 || command.get_value()[0].empty())
		msg = AWAY_DEFAULT;
	else
		msg = command.get_value()[0];
	if (command._user->find_mod("a"))
	{
		command._user->set_mod(command._user->get_mod().erase(command._user->get_mod().find('a'), 1));
		command._server->send_msg(RPL_UNAWAY(command._user->get_hostname()), command._sfd);
		return;
	}
	else
	{
		command._user->set_mod(command._user->get_mod().append("a"));
		command._server->send_msg(RPL_NOWAWAY(command._user->get_hostname()), command._sfd);
		return;
	}
}