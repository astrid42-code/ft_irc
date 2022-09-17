/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_leave.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:28:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/16 17:59:32 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../RPL_answer.hpp"
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

void join(Cmd &command){
	// (void)command;
	std::cout << "_______________________entree dans Join ______________" << std::endl;
	if (!command.get_value().size())
		command._server->get_msg(ERR_NEEDMOREPARAMS(command.get_key()), NULL,command);
	 // if (command._user->isonchan(chan_name) == 0)
        // command._server->get_msg(ERR_NOTONCHANNEL(chan_name), NULL, command);
	Channel *newOne = NULL;
	std::cout << "command.get_value" << command.get_value()[0] << std::endl;
	newOne = command._server->get_chan(command.get_value()[0]);
	std::cout << "Else" << std::endl;
	if(newOne == NULL)
	{
		//std::cout << "NULL" << std::endl;
		newOne = new Channel(command.get_value()[0]);
		command._server->set_chan(newOne);
		std::cout << "NEW CHAN : " << newOne->get_name() << std::endl;

	}
	//command._user->set_chan(*newOne);
	
	// si plsrs channels dans arg1 ils doivent etre separes par des virgules
	// et etre crees separement (le client gere ensuite)
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
	std::cout << "part test" << std::endl;
	// std::cout << "size " << command.get_value().size() << std::endl;
	if (command.get_value().size() < 2){
		command._server->get_msg(ERR_NEEDMOREPARAMS(command.get_key()), command._user,command);
		return;
	}

	// aller recuperer le user (server->get_user_fd())
	// puis avec un iterator it : parcourir le vector de channels dans lesquels est ce user
	// si l'it != end() c'est ok, et remove le channel
	
	// (puis remove le user du channel)
	
	// comment recuperer l'objet channel? ( une ref serait mieux mais comment la faire ici?)
	std::cout << "chan " << command.get_value()[1] << std::endl;
	Channel * chan = command._server->get_chan(command.get_value()[1]);
	if (chan == NULL)
		command._server->get_msg(ERR_NOSUCHCHANNEL(command.get_value()[1]), command._user, command);
	chan->remove_user(command._user);

	// > checker si le user est dans le channel avant de le sortir
	if (command._user->isOnChan(command.get_value()[1])) 
	command._user->remove_chan(chan);
	else{
		command._server->get_msg(ERR_NOTONCHANNEL(command.get_value()[1]), command._user, command);
	}
// a faire en amont : aller verifier qu'au join, le chan est bien set dans la map, et que le user est mis dans le chan
// + passer les get channel et user en & plutot que ptr?

}