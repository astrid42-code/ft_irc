/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_leave.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:28:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/26 10:02:18 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../RPL_answer2.hpp"
#include "../../Server/Server.hpp"


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

void join(Cmd &command)
{
	Channel 					*chan = NULL;
	std::vector<std::string>	chans;
	bool						valid;

	std::cout << "_______________________entree dans Join ______________" << std::endl;
	if (!command.get_value().size())
	{
		command._server->send_msg(461, ERR_NEEDMOREPARAMS(command.get_key()), command);
		return ;
	}
	chans = div_string(command.get_value()[0], ',');
	for (std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		valid = false;
		if (!(chan = command._server->get_chan(*it)))
		{
			chan = new Channel(command.get_value()[0]);
			if (!command._server->set_chan(chan))
				command._server->send_msg(437, ERR_UNAVAILRESOURCE(command.get_value()[0]), command);
			else
			{
				std::cout << "NEW CHAN : |" << chan->get_name() << "|" << std::endl;
				command._server->set_user_in_chan(command._user, chan);
				command._user->set_mod(command._user->get_mod() + "o");
				valid = true;
			}
		}
		else
		{
			if (chan->get_mod().find("i") == std::string::npos)
			{
				if (chan->get_mod().find("I") ==  std::string::npos || (chan->get_mod().find("I") != std::string::npos && mask_off(chan->get_mask(), command._user->get_hostname())))
				{
					command._server->set_user_in_chan(command._user, chan);
					valid = true;
				}
				else
					command._server->send_msg(476, ERR_BADCHANMASK(chan->get_key()), command);
			}
		}
		if (valid == true)
		{
			command._server->send_msg(42, chan->get_name(), command);
			chan->send_to_users(":" + command._user->get_nick() + "!" + command._user->get_user() + "@" + command._user->get_host() + " JOIN " + chan->get_name());
		}
	}
}

// si user deja dans un channel, /join ce meme channel ne fait rien
// on passe d un channel a l'autre avec join (un channel deja cree garde les msgs deja envoyes)

// Command: PART
//    Parameters: <channel> *( "," <channel> ) [ <Part Message> ]

//    The PART command causes the user sending the message to be removed
//    from the list of active members for all given channels listed in the
//    parameter string.  If a "Part Message" is given, this will be sent
//    instead of the default message, the nickname.  This request is always
//    granted by the server.

//    Servers MUST be able to parse arguments in the form of a list of
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
	// (void)command;
	std::cout << "part test" << std::endl;
	std::cout << "size " << command.get_value().size() << std::endl;
	if (command.get_value().size() < 1)
	{
		command._server->send_msg(461, ERR_NEEDMOREPARAMS(command.get_key()), command);
		return;
	}
	std::cout << "chan " << command.get_value()[0] << std::endl;
	Channel * chan = command._server->get_chan(command.get_value()[0]);
	if (chan == NULL)
	{
		std::cout << "chan null" << std::endl;
		command._server->send_msg(403, ERR_NOSUCHCHANNEL(command.get_value()[0]), command);
		return;
	}
	else
		chan->remove_user(command._user);

	// if (command._server->get_chan(command.get_value()[0])->size() == 0)
		

	// std::string tmp = "#";
	// tmp.append(command.get_value()[1]);
	// > checker si le user est dans le channel avant de le sortir
	std::cout << "command.get_value()[0] :" << command.get_value()[0] << std::endl;
	if (command._user->isOnChan(command.get_value()[0]))
	{
		std::cout << "IL EST SUR LE CHAN " << std::endl;
		//command._user->remove_chan(chan);
	}
	else
		command._server->send_msg(442, ERR_NOTONCHANNEL(command.get_value()[0]), command);
// a faire en amont : aller verifier qu'au join, le chan est bien set dans la map, et que le user est mis dans le chan
// + passer les get channel et user en & plutot que ptr?

}

// a faire : boucle while si plss channels
// + quitter le channel