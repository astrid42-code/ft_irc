/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:56:19 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/14 16:35:15 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

// Paramètres : <nom du chan> <nick>
// Réponses possibles : ERR_NEEDMOREPARAMS (461), ERR_NOSUCHCHANNEL (403), ERR_NOTONCHANNEL (442), ERR_CHANOPRIVSNEEDED (482)

// Ce message sert aux ops à éjecter un utilisateur de force du chan. 

//       Command: KICK
//    Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
//                [<comment>]

//    The KICK command can be used to request the forced removal of a user
//    from a channel.  It causes the <user> to PART from the <channel> by
//    force.  For the message to be syntactically correct, there MUST be
//    either one channel parameter and multiple user parameter, or as many
//    channel parameters as there are user parameters.  If a "comment" is
//    given, this will be sent instead of the default message, the nickname
//    of the user issuing the KICK.

//    The server MUST NOT send KICK messages with multiple channels or
//    users to clients.  This is necessarily to maintain backward
//    compatibility with old client software.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//            ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
//            ERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL

//    Examples:

//    KICK &Melbourne Matthew         ; Command to kick Matthew from
//                                    &Melbourne

//    KICK #Finnish John :Speaking English
//                                    ; Command to kick John from #Finnish
//                                    using "Speaking English" as the
//                                    reason (comment).

//    :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
//                                    ; KICK message on channel #Finnish
//                                    from WiZ to remove John from channel

void kick(Cmd &command)
{
	std::cout << "kick test" << '\n';  
	if (command.get_value().size() < 2)
		command._server->get_msg(ERR_NEEDMOREPARAMS(command.get_key()), command._user,command);
	if (command._user->get_mod().find("o") != std::string::npos)
	{
		Channel *chan;
		if ((chan = command._server->get_chan(command.get_value()[0])) != NULL)
		{
			User *user;
			if ((user = chan->get_user(command.get_value()[1])) != NULL)
			{
				std::cout << "you kicked " << command._user->get_nick() << " from " << command.get_value()[0] << " chan..." << std::endl;
				user->remove_chan(chan); // need to include comment into the kick message...
			}
			else
				command._server->get_msg(ERR_USERNOTINCHANNEL(command.get_value()[1], command.get_value()[0]), NULL, command);
		}
		else
			command._server->get_msg(ERR_NOSUCHCHANNEL(command.get_value()[0]), NULL, command);
	}
	else
		command._server->get_msg(ERR_CHANOPRIVSNEEDED(command.get_value()[0]), NULL, command);
}