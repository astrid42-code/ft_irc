/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:38:02 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/22 16:37:01 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


// Message LIST
// Paramètres : [<nom du chan>]
// Réponses possibles : RPL_LISTSTART (321) (obsolete, not used), RPL_LIST (322), RPL_LISTEND (323)

// Permet de demander la liste des chans, ou les détails sur un chan en particulier. 

//   Command: LIST
//    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

//    The list command is used to list channels and their topics.  If the
//    <channel> parameter is used, only the status of that channel is
//    displayed.

//    If the <target> parameter is specified, the request is forwarded to
//    that server which will generate the reply.

//    Wildcards are allowed in the <target> parameter.

//    Numeric Replies:

//            ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
//            RPL_LIST                        RPL_LISTEND

//    Examples:

//    LIST                            ; Command to list all channels.

//    LIST #twilight_zone,#42         ; Command to list channels
//                                    #twilight_zone and #42

void list(Cmd &command)
{
	std::cout << "list test" << std::endl;
	if (command.get_size() == 0)
	{
		std::map<std::string, Channel *> chan = command._server->get_chans();

		for (std::map<std::string, Channel *>::iterator it = chan.begin(); it != chan.end(); it++)
		{
			if (it->second->get_mod().find('s') == std::string::npos && it->second->get_mod().find('p') == std::string::npos)
				command._server->send_msg(322, RPL_LIST(it->first, it->second->get_mod(), it->second->get_topic()), command);
		}
		command._server->send_msg(323, RPL_LISTEND, command);
	}
	else
	{
		Channel 		*chan;
		unsigned long	i = 0;
		unsigned long	j;
		std::string	tmp;

		while (i < command.get_value()[0].size())
		{
			j = i;
			i = command.get_value()[0].find(',', j);
			if (i == std::string::npos)
				i = command.get_value()[0].size();
			tmp = command.get_value()[0].substr(j, i - j);
			std::cout << "|" << tmp << "|" << std::endl;
			if ((chan = command._server->get_chan(tmp)) != NULL)
			{
				if (chan->get_mod().find('s') == std::string::npos && chan->get_mod().find('p') == std::string::npos)
					command._server->send_msg(322, RPL_LIST(chan->get_key(), chan->get_mod(), chan->get_topic()), command);
			}
			else
				command._server->send_msg(402, ERR_NOSUCHSERVER, command);
			
		}
		command._server->send_msg(323, RPL_LISTEND, command);
	}
	// tant que la liste de channels (separes par une ,) n est pas finie
	// verifier si le channel existe dans la map de channels (et si arg[1] rajouter le topic associe)
}