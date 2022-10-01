/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_leave.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:28:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 16:57:16 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../RPL_answer.hpp"
#include "../../Server/Server.hpp"

// Paramètres : <nom du chan> [<clé>]

bool		join_conditions(Channel *chan, Cmd &command, size_t i, std::vector<std::string>	keys)
{
	if (command.get_value().size() >= 2 && i < keys.size() && keys[i].compare(chan->get_key()) != 0)
	{
		command._server->send_msg(ERR_BADCHANNELKEY(command._user->get_hostname(), chan->get_name()), command._sfd);
		return (false);
	}
	if (chan->get_mod().find("i") != std::string::npos)
	{
		command._server->send_msg(ERR_INVITEONLYCHAN(command._user->get_hostname(), chan->get_name()), command._sfd);
		return (false);
	}
	if ((chan->get_mod().find("l") != std::string::npos) && (chan->get_limit() == chan->get_users().size()))
	{
		command._server->send_msg(ERR_CHANNELISFULL(command._user->get_hostname(), chan->get_name()), command._sfd);
		return (false);
	}
	if ((chan->get_mod().find("I") != std::string::npos) && !mask_off(chan->get_mask() ,command._user->get_hostname()))
	{
		command._server->send_msg(ERR_BADCHANMASK(command._user->get_hostname(), chan->get_name()), command._sfd);
		return (false);
	}
	return (true);
}

bool		bad_chan(std::string chan_name, Cmd &command)
{
	if (chan_name.compare("#") == 0 || (chan_name.find("!") == 0) || (chan_name.find("@") == 0))
	{
		command._server->send_msg(ERR_NOSUCHCHANNEL(command._user->get_hostname(), command._user->get_nick(), chan_name), command._sfd);
		return (false);
	}
	return (true);
}

void	join(Cmd &command)
{
	Channel 					*chan = NULL;
	std::vector<std::string>	chans;
	std::vector<std::string>	keys;
	bool						valid;

	std::cout << "______________Join ______________" << std::endl;
	if (command.get_value().size() < 1)
	{
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
		return;		
	}
	chans = div_string(command.get_value()[0], ',');
	if (command.get_value().size() == 2)
		keys = div_string(command.get_value()[1], ',');
	for (size_t i = 0; i < chans.size(); i++)
	{
		valid = false;
		if (!(chan = command._server->get_chan(chans[i])))
		{
			if (bad_chan(chans[i], command))
			{
				chan = new Channel(chans[i]);
				if (!command._server->set_chan(chan))
					command._server->send_msg(ERR_UNAVAILRESOURCE(command._user->get_hostname(), command.get_value()[0]), command._sfd);
				else
				{
					command._server->set_user_in_chan(command._user, chan);
					if (!command._user->find_mod("o"))
						command._user->set_mod(command._user->get_mod() + "o");
					valid = true;
				}
			}
		}
		else
		{
			if (join_conditions(chan, command, i, keys))
			{
					command._server->set_user_in_chan(command._user, chan);
					valid = true;
			}
		}
		if (valid == true)
		{
			std::map< int, User *>	users = chan->get_users();
			command._server->send_msg(RPL_TOPIC(command._user->get_hostname(), chan->get_name(), chan->get_topic()), command._sfd);
			for (std::map< int, User *>::iterator it = users.begin(); it != users.end(); it++)
				command._server->send_msg(RPL_NAMREPLY(command._user->get_hostname(), chan->get_name(), it->second->get_nick()), command._sfd);
			command._server->send_msg(RPL_ENDOFNAMES(command._user->get_hostname(), command._user->get_nick(), chan->get_name()), command._sfd);
			chan->send_to_users(JOIN(command._user->get_hostname(),chan->get_name()));
		}
	}
}

// Command: PART
//    Parameters: <channel> *( "," <channel> ) [ <Part Message> ]

void part(Cmd &command)
{
	Channel						*chan;
	std::vector<std::string>	args;
	std::vector<Channel *>		*chans;
	std::string					msg;

	if (command.get_value().size() < 1)
	{
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
		return;
	}
	if (command.get_size() == 2)
		msg = command.get_value()[1];
	else
		msg = "Ciao !!";
	args = div_string(command.get_value()[0], ',');
	for (size_t i = 0; i < args.size(); i++)
	{
		if ((chan = command._server->get_chan(args[i])) == NULL)
			command._server->send_msg(ERR_NOSUCHCHANNEL(command._user->get_hostname(), command._user->get_nick(), command.get_value()[0]), command._sfd);
		else
		{
			if (!command._user->get_channel(args[i]))
				command._server->send_msg(ERR_NOTONCHANNEL(command._user->get_hostname(), command.get_value()[0]), command._sfd);
			else	
			{
				chan->send_to_users(PART(command._user->get_hostname(),chan->get_name(),msg));
				chan->remove_user(command._user);
				chans = command._user->get_chans();
				if (command._user->it_chan(chan->get_name()) != chans->end())
					chans->erase(command._user->it_chan(chan->get_name()));
				if (erase_chan(chan, command._user))
				{
					command._server->get_chans()->erase(chan->get_name());
					delete chan;
				}
			}
		}
	}
}