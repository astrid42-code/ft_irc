/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:56:19 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/30 19:20:08 by asgaulti         ###   ########.fr       */
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

bool	kick_check(Cmd &command)
{
	if (command.get_value().size() < 2)
	{
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(),command.get_key()), command._sfd);
		return (false);
	}
	if (command._user->get_mod().find("o") == std::string::npos)
	{
		command._server->send_msg(ERR_CHANOPRIVSNEEDED(command._user->get_hostname(), command.get_value()[0]), command._sfd);
		return (false);
	}
	return (true);
}

void	kick(Cmd &command)
{
	Channel						*chan;
	User						*user;
	std::vector<std::string>	chans = div_string(command.get_value()[0], ',');
	std::vector<std::string>	users = div_string(command.get_value()[1], ',');

	std::cout << "kick test" << std::endl;
	if (!kick_check(command))
		return ;
	if (chans.size() == 1)
	{
		if ((chan = command._server->get_chan(chans[0])) != NULL)
		{
			if ((user = chan->get_user(users[0])) != NULL)
			{
				std::cout << "you kicked " << command._user->get_nick() << " from " << command.get_value()[0] << " chan..." << std::endl;
				user->remove_chan(chan); // need to include comment into the kick message...
				command._server->send_msg(KICK(command._user->get_hostname(), chans[0], users[0]), command._sfd);
			}
			else
				command._server->send_msg(ERR_USERNOTINCHANNEL(command._user->get_hostname(),command.get_value()[1], command.get_value()[0]), command._sfd);
		}
		else
			command._server->send_msg(ERR_NOSUCHCHANNEL(command._user->get_hostname(), command._user->get_nick(),command.get_value()[0]), command._sfd);
	}
	else if (chans.size() > 1 && chans.size() == users.size())
	{
		for (size_t i = 0; i < chans.size(); i++)
		{
			if ((chan = command._server->get_chan(chans[i])) != NULL)
			{
				if ((user = chan->get_user(users[i])) != NULL)
				{
					std::cout << "you kicked " << command._user->get_nick() << " from " << command.get_value()[0] << " chan..." << std::endl;
					user->remove_chan(chan); // need to include comment into the kick message...
					command._server->send_msg(KICK(command._user->get_hostname(), chans[i], users[i]), command._sfd);
				}
				else
					command._server->send_msg(ERR_USERNOTINCHANNEL(command._user->get_hostname(),users[i], chans[i]), command._sfd);
			}
			else
				command._server->send_msg(ERR_NOSUCHCHANNEL(command._user->get_hostname(), command._user->get_nick(), command.get_value()[0]), command._sfd);
		}
	}
	else
		command._server->send_msg(ERR_CHANOPRIVSNEEDED(command._user->get_hostname(), command.get_value()[0]), command._sfd);
}