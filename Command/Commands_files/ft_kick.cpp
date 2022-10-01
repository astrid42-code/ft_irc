/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:56:19 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 16:58:24 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

// Paramètres : <nom du chan> <nick>

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

	if (!kick_check(command))
		return ;
	if (chans.size() == 1 && users.size() == 1)
	{
		if ((chan = command._server->get_chan(chans[0])) != NULL)
		{
			if ((user = chan->get_user(users[0])) != NULL)
			{
				chan->send_to_users(KICK(command._user->get_hostname(), chans[0], users[0]));
				user->remove_chan(chan);
				command._server->send_msg(KICK(command._user->get_hostname(), chans[0], users[0]), command._sfd);
			}
			else
				command._server->send_msg(ERR_USERNOTINCHANNEL(command._user->get_hostname(), command._user->get_nick() ,command.get_value()[1], command.get_value()[0]), command._sfd);
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
					chan->send_to_users(KICK(command._user->get_hostname(), chans[i], users[i]));
					user->remove_chan(chan);
					command._server->send_msg(KICK(command._user->get_hostname(), chans[i], users[i]), command._sfd);
				}
				else
					command._server->send_msg(ERR_USERNOTINCHANNEL(command._user->get_hostname(), command._user->get_nick(), users[i], chans[i]), command._sfd);
			}
			else
				command._server->send_msg(ERR_NOSUCHCHANNEL(command._user->get_hostname(), command._user->get_nick(), command.get_value()[0]), command._sfd);
		}
	}
	else
		command._server->send_msg(ERR_CHANOPRIVSNEEDED(command._user->get_hostname(), command.get_value()[0]), command._sfd);
}