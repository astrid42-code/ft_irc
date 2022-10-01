/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_leave.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:28:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 10:42:04 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../RPL_answer.hpp"
#include "../../Server/Server.hpp"
// #include "../../utils.cpp"

// Paramètres : <nom du chan> [<clé>]
// Réponses possibles : ERR_NEEDMOREPARAMS (461), ERR_BANNEDFROMCHAN (474), ERR_INVITEONLYCHAN (473), ERR_BADCHANNELKEY (475), ERR_CHANNELISFULL (471), ERR_NOSUCHCHANNEL (403), RPL_TOPIC (332)

// Ce message permet d'entrer sur un chan. Une fois qu'un utilisateur est sur un chan, il reçoit tous les messages (discussion et gestion) concernant ce chan. Si l'entrée est validée, le serveur transmet le message aux autres serveurs et autres utilisateurs présents sur le chan, puis le message RPL_TOPIC rappelle le topic du chan, et est suivi de messages RPL_NAMREPLY (353) avec la liste des nicks présents sur le chan, et enfin par un RPL_ENDOFNAMES (366). 

// command: JOIN
//    Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
//                / "0"

//    The JOIN command is used by a user to request to start listening to
//    the specific channel.  Servers MUST be able to parse arguments in the
//    form of a list of target, but SHOULD NOT use lists when sending JOIN
//    messages to clients.

//    Once a user has joined a channel, he receives information about
//    all commands his server receives affecting the channel.  This
//    includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
//    This allows channel members to keep track of the other channel
//    members, as well as channel modes.

//    If a JOIN is successful, the user receives a JOIN message as
//    confirmation and is then sent the channel's topic (using RPL_TOPIC) and
//    the list of users who are on the channel (using RPL_NAMREPLY), which
//    MUST include the user joining.

//    Note that this message accepts a special argument ("0"), which is
//    a special request to leave all channels the user is currently a member
//    of.  The server will process this message as if the user had sent
//    a PART command (See Section 3.2.2) for each channel he is a member
//    of.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//            ERR_CHANNELISFULL               ERR_BADCHANMASK
//            ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//            ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
//            RPL_TOPIC

//    Examples:

//    JOIN #foobar                    ; Command to join channel #foobar.

//    JOIN &foo fubar                 ; Command to join channel &foo using
//                                    key "fubar".

//    JOIN #foo,&bar fubar            ; Command to join channel #foo using
//                                    key "fubar" and &bar using no key.

//    JOIN #foo,#bar fubar,foobar     ; Command to join channel #foo using
//                                    key "fubar", and channel #bar using
//                                    key "foobar".

//    JOIN #foo,#bar                  ; Command to join channels #foo and
//                                    #bar.

//    JOIN 0                          ; Leave all currently joined
//                                    channels.

//    :WiZ!jto@tolsun.oulu.fi JOIN #Twilight_zone ; JOIN message from WiZ
//                                    on channel #Twilight_zone

bool		join_conditions(Channel *chan, Cmd &command)
{
	bool	res = true;

	if (chan->get_mod().find("i") != std::string::npos)
	{
		command._server->send_msg(ERR_INVITEONLYCHAN(command._user->get_hostname(), chan->get_name()), command._sfd);
		res = false;
		return (res);
	}
	if ((chan->get_mod().find("l") != std::string::npos) && (chan->get_limit() == chan->get_users().size()))
	{
		command._server->send_msg(ERR_CHANNELISFULL(command._user->get_hostname(), chan->get_name()), command._sfd);
		res = false;
		return (res);
	}
	if ((chan->get_mod().find("I") != std::string::npos) && !mask_off(chan->get_mask() ,command._user->get_hostname()))
	{
		command._server->send_msg(ERR_BADCHANMASK(command._user->get_hostname(), chan->get_name()), command._sfd);
		res = false;
		return (res);
	}
	return (res);
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

	std::cout << "_______________________entree dans Join ______________" << std::endl;
	if (!command.get_value().size()){
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
		return;		
	}
	chans = div_string(command.get_value()[0], ',');
	if(command.get_value().size() == 2)
		keys = div_string(command.get_value()[1], ',');
	for (size_t i = 0; i < chans.size(); i++)
	{
		valid = false;
		if (!(chan = command._server->get_chan(chans[i])))
		{
			if (bad_chan(chans[i], command))
			{
				std::cout << "chanel creation..." << std::endl;
				chan = new Channel(chans[i]);
				if (!command._server->set_chan(chan)){
					command._server->send_msg(ERR_UNAVAILRESOURCE(command._user->get_hostname(), command.get_value()[0]), command._sfd);
					return;
				}
				else
				{
					std::cout << "NEW CHAN : |" << chan->get_name() << "|" << std::endl;
					command._server->set_user_in_chan(command._user, chan);
					if (!command._user->find_mod("o"))
					{
						std::cout << "inside creator op chan" << std::endl;
						command._user->set_mod(command._user->get_mod() + "o");
						std::cout << command._user->find_mod("o") << std::endl;
					}
					valid = true;
				}
			}
		}
		else
		{
			if (command.get_value().size() >= 2 && i < keys.size() && keys[i].compare(chan->get_key()) != 0){
				command._server->send_msg(ERR_BADCHANNELKEY(command._user->get_hostname(), chan->get_name()), command._sfd);
				return;
			}
			else
			{
				std::cout << "user joining chanel..." << std::endl;
				if (join_conditions(chan, command))
				{
						command._server->set_user_in_chan(command._user, chan);
						valid = true;
				}
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
			return;
		}
	}
}

// si user deja dans un channel, /join ce meme channel ne fait rien
// on passe d un channel a l'autre avec join (un channel deja cree garde les msgs deja envoyes)

// Command: PART
//    Parameters: <channel> *( "," <channel> ) [ <Part Message> ]

//    The PART command causes the user sendiNOSUCHCHs in the form of a list of
//    target, but SHOULD NOT use lists when sending PART messages to
//    clients.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//            ERR_NOTONCHANNEL

//    Examples:

//    PART #twilight_zone             ; Command to leave channel
//                                    "#twilight_zone"

//    PART #oz-ops,&group5            ; Command to leave both channels
//                                    "&group5" and "#oz-ops".

//    :WiZ!jto@tolsun.oulu.fi PART #playzone :I lost
//                                    ; User WiZ leaving channel
//                                    "#playzone" with the message "I
//                                    lost".

void part(Cmd &command)
{
	Channel						*chan;
	std::vector<std::string>	args;
	std::vector<Channel *>		*chans;

	std::cout << "part test" << std::endl;
	if (command.get_value().size() < 1)
	{
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
		return;
	}
	args = div_string(command.get_value()[0], ',');
	for (size_t i = 0; i < args.size(); i++)
	{
		chan = command._server->get_chan(args[i]);
		// std::cout << "chan name : " << chan->get_name() << std::endl;
		if (chan == NULL)
		{
			command._server->send_msg(ERR_NOSUCHCHANNEL(command._user->get_hostname(), command._user->get_nick(), command.get_value()[0]), command._sfd);
			continue;
		}
		if (!command._user->get_channel(args[i])){
			command._server->send_msg(ERR_NOTONCHANNEL(command._user->get_hostname(), command.get_value()[0]), command._sfd);
			return;
		}
		else	
		{
			std::string msg;
			if (command.get_size() == 2)
				msg = command.get_value()[1];
			else
				msg = "Ciao !!";
			chan->send_to_users(PART(command._user->get_hostname(),chan->get_name(),msg));
			chan->remove_user(command._user);
			chans = command._user->get_chans();
			if (command._user->it_chan(chan->get_name()) != chans->end())
				chans->erase(command._user->it_chan(chan->get_name()));
			if (erase_chan(chan, command._user))
			{
				std::cout << "erase_chan" << std::endl;
				command._server->get_chans()->erase(chan->get_name());
				delete chan;
				std::cout << "size map de chans : " << command._server->get_chans()->size() << std::endl;
			}
		}
	}
}