/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:56:57 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:33:29 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../Server/Server.hpp"


// Command: NICK
//    Parameters: <nickname>

void nick(Cmd &command)
{
	if (command.get_size() == 0)
		command._server->send_msg(ERR_NONICKNAMEGIVEN(command._user->get_hostname()), command._sfd);
	else
	{
		command.get_value()[0] = to_upper(command.get_value()[0]);
		if (command._server->get_user(command.get_value()[0]) == NULL && command.get_value()[0].compare("anonymous") != 0)
		{
			if (command._user->get_valid() == 1)
				command._user->set_valid(2);
			else
				command._server->send_msg(NICK(command._user->get_hostname(), command.get_value()[0]), command._sfd);
			command._user->set_nick(command.get_value()[0]);
		}
		else
			command._server->send_msg(ERR_NICKNAMEINUSE(command._user->get_hostname(), command.get_value()[0]), command._sfd);
	}
}
