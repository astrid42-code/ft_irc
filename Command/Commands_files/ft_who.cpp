/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_who.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:42 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/23 09:50:05 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"



//       Command: WHO
//    Parameters: [ <mask> [ "o" ] ]

//    The WHO command is used by a client to generate a query which returns
//    a list of information which 'matches' the <mask> parameter given by
//    the client.  In the absence of the <mask> parameter, all visible
//    (users who aren't invisible (user mode +i) and who don't have a
//    common channel with the requesting client) are listed.  The same
//    result can be achieved by using a <mask> of "0" or any wildcard which
//    will end up matching every visible user.

//    The <mask> passed to WHO is matched against users' host, server, real
//    name and nickname if the channel <mask> cannot be found.

//    If the "o" parameter is passed only operators are returned according
//    to the <mask> supplied.

//    Numeric Replies:

//            ERR_NOSUCHSERVER
//            RPL_WHOREPLY                  RPL_ENDOFWHO

//    Examples:

//    WHO *.fi                        ; Command to list all users who match
//                                    against "*.fi".

//    WHO jto* o                      ; Command to list all users with a
//                                    match against "jto*" if they are an
//                                    operator.

void	who(Cmd &command)
{
	std::map<int, User *>	users = command._server->get_users();
	std::vector<Channel *>	chans = command._user->get_chans();
	bool					match = false;
	bool					serv;

	std::cout << "who test" << std::endl;
	for (std::map<int, User *>::iterator itu = users.begin(); itu != users.end(); itu++)
	{
		if (itu->second->get_mod().find('i') == std::string::npos && itu->second != command._user)
		{
			if (command.get_size() >= 1 && command.get_value()[1][0] != '0' && command.get_value()[1].compare("*") != 0)
			{
				if (mask_off(command.get_value()[1], itu->second->get_hostname()) || mask_off(command.get_value()[1], itu->second->get_name()) || mask_off(command.get_value()[1], SERVER))
				{
					if (command.get_size() == 1 || (command.get_size() == 2 && command.get_value()[2][0] == 'o' && itu->second->find_mod("o")))
					{
						command._server->send_msg(RPL_WHOREPLY(command._user->get_hostname(), itu->second->get_channel_name(), itu->second->get_user(), itu->second->get_host(), itu->second->get_nick(), itu->second->get_name()), command._sfd);
						match = true;
					}
				}
			}
			else
			{
				serv = true;
				for (std::vector<Channel *>::iterator itc = chans.begin(); itc != chans.end(); itc++)
				{
					if (itu->second->find_mod("i") || itu->second->get_channel((*itc)->get_key()) != NULL)
						serv = false;
				}
				if (serv)
				{
					std::cout << "user is not in the same serv..." << std::endl;
					if (command.get_size() < 2 || (command.get_size() == 2 && command.get_value()[2][0] == 'o' && itu->second->find_mod("o")))
					{
						command._server->send_msg(RPL_WHOREPLY(command._user->get_hostname(), itu->second->get_channel_name(), itu->second->get_user(), itu->second->get_host(), itu->second->get_nick(), itu->second->get_name()), command._sfd);
						match = true;
					}
				}
			}
		}
	}
	if (match == true)
		command._server->send_msg(RPL_ENDOFWHO(command._user->get_hostname(), command._server->get_ip()), command._sfd);
}