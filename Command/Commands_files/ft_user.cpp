/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_user.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:18:44 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:13:04 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

// Command: USER
//    Parameters: <user> <mode> <unused> <realname>

void user(Cmd &command)
{
	std::vector<std::string>::iterator it;

    if (command.get_size() != 4)
	{
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
		return ;
	}
	if (command.get_value()[0].compare("anonymous") == 0 || command.get_value()[2].compare("anonymous") == 0)
	{
		command._server->send_msg(ERR_ALREADYREGISTRED(command._user->get_hostname()), command._sfd);
		return;
	}
	if (command._user->get_valid() == 2)
		command._user->set_valid(3);
	else
		return ;
	command._user->set_user(command.get_value()[0]);
	command._user->set_host(command.get_value()[2]);
	command._user->set_name(command.get_value()[3]);
	command._user->set_mod("");
	command._user->set_sfd(command._sfd);
	command._server->set_user(command._user);

	command._server->send_msg(RPL_WELCOME(command._user->get_hostname(), command._user->get_nick()) ,command._sfd);
	command._server->send_msg(RPL_YOURHOST(command._user->get_hostname()),command._sfd);
	command._server->send_msg(RPL_CREATED(command._user->get_hostname()),command._sfd);
	command._server->send_msg(RPL_MYINFO(command._user->get_hostname()),command._sfd);
	command._server->send_msg(RPL_MOTDSTART(command._user->get_hostname()) , command._sfd);
	command._server->send_msg(RPL_MOTD(command._user->get_hostname(), PINGU) , command._sfd);
	command._server->send_msg(RPL_ENDOFMOTD(command._user->get_hostname()) , command._sfd);
}