/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oper.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:00:36 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:06:09 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


//  Command: OPER
//    Parameters: <name> <password>


void oper(Cmd &command)
{
	if (command.get_size() != 2)
	{
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
		return;
	}
	if (command._user->get_nick().compare(command.get_value()[0]) == 0)
	{
		if (command._server->get_pwd() != command.get_value()[1])
			command._server->send_msg(ERR_PASSWDMISMATCH(command._user->get_hostname(), command._user->get_nick()), command._sfd);
		else
		{
			if (!command._user->find_mod("o"))
			{
				command._user->set_mod(command._user->get_mod() + "o");
				command._server->send_msg(RPL_YOUREOPER(command._user->get_hostname()), command._sfd);
			}
		}
	}
	else
		command._server->send_msg(ERR_NOOPERHOST(command._user->get_hostname()), command._sfd);
}