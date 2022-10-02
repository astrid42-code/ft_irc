/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:31:20 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:06:51 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../RPL_answer.hpp"

// Command: PASS
//    Parameters: <password>

void pass(Cmd &command)
{
    if (command.get_value().size() != 1)
	{
        command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
		return;
    }
    else
	{
		if (command._server->get_pwd().compare(command.get_value()[0]) == 0)
		{
			if (command._user->get_valid() == 0)
				command._user->set_valid(1);
		}
		else
			command._server->send_msg(ERR_PASSWDMISMATCH(command._user->get_hostname(), command._user->get_nick()), command._sfd);
	}
}