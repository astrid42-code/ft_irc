#ifndef RPL_ANSWER_HPP
#define RPL_ANSWER_HPP

#include <iostream>
#include "Cmd.hpp"

#define SERVERNAME "irc_dta"
#define SERVER "127.0.0.1"  // adresse ip ex : Your host is 62.210.33.192, running version 1.69
#define VERSION "1.69" // version actuelle a verifier
#define DATE "Mon Aug 5 16:57:33 2022"
#define DEFAULT_NAME "toto"


//#define RPL_WELCOME ("Welcome to the Internet Relay Network\r\n") //001
        	// + envoyer <nick>!<user>@<host>) en arguments
			// + ajouter dessin?

//#define RPL_YOURHOST ( "Your host is " SERVER ", running version" VERSION "\r\n") //002

//#define RPL_CREATED ("This server was created " DATE "\r\n") // 003

//#define RPL_MYINFO(user_mode, chan_mode) (SERVERNAME VERSION "<available user modes> <available channel modes>\r\n") // 004
	// + envoyer nombre de users en fct de leur mode (nbr de users connectes, nbre d'invisible users connectes)
	// (prevoir fcts dans class users pour comptabiliser les users co en fct de leurs statuts, a envoyer en arguments)
	//  et channels avalaible en arg

#define RPL_AWAY(nick) (nick + " :You have been marked as being away\r\n") // 301
	// + envoyer nick du user en arg

#define RPL_WHOISUSER(nick, user, host, name) (nick + " " + user + " " + host + "* :" + name + "\r\n") // 311
	// + envoyer nick du user, user (?), host et real name en arg

#define RPL_WHOISSERVER(nick, server_info) (nick + " " + SERVER + " :" + server_info + "\r\n") // 312
	// + envoyer nick du user et server info (?)

#define RPL_WHOISOPERATOR(nick) (nick + " :is an IRC operator\r\n") // 313

#define RPL_ENDOFWHO(name) (name + " :End of WHO list\r\n") // 315
	// + envoyer nick (?) du user en arg
// - The RPL_WHOREPLY and RPL_ENDOFWHO pair are used to answer a WHO message.  The RPL_WHOREPLY is only
// sent if there is an appropriate match to the WHO query.  If there is a list of parameters supplied
// with a WHO message, a RPL_ENDOFWHO MUST be sent after processing each list item with <name> being the item.

#define RPL_WHOISIDLE(nick) (nick + " <integer> :seconds idle\r\n") // 317
	// + envoyer nick et integer(??)

#define RPL_ENDOFWHOIS(nick) (nick + " :End of WHOIS list\r\n") // 318

#define RPL_WHOISCHANNELS(nick, channel) (nick + " :*( ( "@" / "+" ) " + channel + " \r\n" ) // 319 (verifier syntaxe du msg)
	// + envoyer channel et nick du user en arg
// - Replies 311 - 313, 317 - 319 are all replies
//            generated in response to a WHOIS message.  Given that
//            there are enough parameters present, the answering
//            server MUST either formulate a reply out of the above
//            numerics (if the query nick is found) or return an
//            error reply.  The '*' in RPL_WHOISUSER is there as
//            the literal character and not as a wild card.  For
//            each reply set, only RPL_WHOISCHANNELS may appear
//            more than once (for long lists of channel names).
//            The '@' and '+' characters next to the channel name
//            indicate whether a client is a channel operator or
//            has been granted permission to speak on a moderated
//            channel.  The RPL_ENDOFWHOIS reply is used to mark
//            the end of processing a WHOIS message.

#define RPL_LIST(channel, mode, topic) (channel + " " +  mode + " :" + topic + "\r\n") // 322
	// + envoyer channel, mode visible (?) et topic (sujet du chan) en arg

#define RPL_LISTEND (":End of LIST\r\n") // 323
//  - Replies RPL_LIST, RPL_LISTEND mark the actual replies
//    with data and end of the server's response to a LIST
//    command.  If there are no channels available to return,
//    only the end reply MUST be sent.

#define RPL_TOPIC(channel, topic) (channel + " :" + topic + "\r\n") // 332
	// + envoyer channel et topic (sujet du chan) en arg
// When sending a TOPIC message to determine the channel topic, one of two replies is sent.  If
// the topic is set, RPL_TOPIC is sent back else RPL_NOTOPIC.

#define RPL_INVITING(channel, nick) (channel + nick + "\r\n") // 341
	// + envoyer channel et nick du user en arg
// Returned by the server to indicate that the attempted INVITE message was successful and is
// being passed onto the end client.

// #define RPL_WHOREPLY(channel, user, host, nick, hopcount, name) (channel + " " + user + " " + host + " " + SERVER + " " + nick + "( "H" / "G" > ["*"] [ ( "@" / "+" ) ]) : " + hopcount + " " + name + "\r\n") // 352
	// envoyer les args

#define RPL_NAMREPLY(channel, nick) ("( "=" / "*" / "@" )" + channel + " :[ "@" / "+" ] " + nick + " *( " " [ "@" / "+" ] " + nick + "\r\n") // 353
	// + envoyer channel et nick du user en arg
//  - "@" is used for secret channels, "*" for private
//    channels, and "=" for others (public channels).

#define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list\r\n") // 366
	// + envoyer channel en arg
// To reply to a NAMES message, a reply pair consisting
//            of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
//            server back to the client.  If there is no channel
//            found as in the query, then only RPL_ENDOFNAMES is

#define RPL_YOUREOPER (":You are now an IRC operator\r\n") // 381
// RPL_YOUREOPER is sent back to a client which has just successfully issued an OPER message and gained operator status.

#define ERR_NOSUCHNICK(nick) (nick + " :No such nick/channel\r\n") // 401
	// + envoyer nick du user en arg
// Used to indicate the nickname parameter supplied to a command is currently unused.

#define ERR_NOSUCHSERVER (SERVER " :No such server\r\n") // 402
// - Used to indicate the server name given currently does not exist.

#define ERR_NOSUCHCHANNEL(channel) (channel + " :No such channel\r\n") // 403
	// + envoyer channel name en arg
// Used to indicate the given channel name is invalid.

#define ERR_CANNOTSENDTOCHAN(channel) (channel + " :Cannot send to channel\r\n") // 404
	// + envoyer channel name en arg
// - Sent to a user who is either (a) not on a channel which is mode +n or (b) not a chanop (or mode +v) on
//  a channel which has mode +m set or where the user is
//  banned and is trying to send a PRIVMSG message to that channel.


#define ERR_TOOMANYCHANNELS(channel) (channel + " :You have joined too many channels\r\n") // 405
	// + envoyer channel name en arg
// - Sent to a user when they have joined the maximum number of allowed channels and they try to join
// another channel.

#define ERR_TOOMANYTARGETS(target) (target + " :<error code> recipients. <abort message>\r\n") // 407
	// + envoyer target (user?) en arg
//  - Returned to a client which is attempting to send a
//    PRIVMSG/NOTICE using the user@host destination format
//    and for a user@host which has several occurrences.

//  - Returned to a client which trying to send a
//    PRIVMSG/NOTICE to too many recipients.

//  - Returned to a client which is attempting to JOIN a safe
//    channel using the shortname when there are more than one
//    such channel.

#define ERR_NORECIPIENT (":No recipient given (<command>)\r\n") // 411 

#define ERR_NOTEXTTOSEND (":No text to send\r\n") // 412

#define ERR_NOTOPLEVEL ("<mask> :No toplevel domain specified\r\n") // 413

#define ERR_WILDTOPLEVEL ("<mask> :Wildcard in toplevel domain\r\n") // 414

#define ERR_NONICKNAMEGIVEN (":No nickname given\r\n") // 431
// - Returned when a nickname parameter expected for a command and isn't found.

#define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname\r\n") // 432
	// + envoyer nick en arg
// - Returned after receiving a NICK message which contains
//            characters which do not fall in the defined set.  See
//            section 2.3.1 for details on valid nicknames.

#define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use\r\n") // 433
	// + envoyer nick en arg
// - Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.

#define ERR_NICKCOLLISION(nick, user, host) (nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n") // 436 
	// + envoyer nick, user (nom dans l'email?) et host (fin adresse mail ?) en arg
// - Returned by a server to a client when it detects a nickname collision (registered of a NICK that
// already exists by another server).

#define ERR_UNAVAILRESOURCE(nick_chan) (nick_chan + " :Nick/channel is temporarily unavailable\r\n") // 437
	// + envoyer channel ou nick en arg
// - Returned by a server to a user trying to join a channel
//            currently blocked by the channel delay mechanism.

// - Returned by a server to a user trying to change nickname
//            when the desired nickname is blocked by the nick delay
//            mechanism.

#define ERR_USERNOTINCHANNEL(nick, channel) (nick + " " + channel + " :They aren't on that channel\r\n") // 441
	// + envoyer user et channel en arg
// - Returned by the server to indicate that the target user of the command is not on the given channel.

#define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel\r\n") // 442
	// + envoyer nom du channel en arg
// Returned by the server whenever a client tries to perform a channel affecting command for which the
// client isn't a member.

#define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel\r\n") // 443
	// + envoyer user et channel en arg
// Returned when a client tries to invite a user to a channel they are already on.

#define ERR_NOTREGISTERED (":You have not registered\r\n") //451
// Returned by the server to indicate that the client MUST be registered before the server will allow it
// to be parsed in detail.

#define ERR_NEEDMOREPARAMS(key) (key + " :Not enough parameters\r\n") // 461
	// + envoyer key (nom de cmd) en arg
// Returned by the server by numerous commands to indicate to the client that it didn't supply enough parameters.

#define ERR_ALREADYREGISTRED (":Unauthorized command (already registered)\r\n") // 462
// Returned by the server to any link which tries to change part of the registered details (such as
// password or user details from second USER message).

#define ERR_PASSWDMISMATCH (":Password incorrect\r\n") // 464
// Returned to indicate a failed attempt at registering a connection for which a password was required and
// was either not given or incorrect.

#define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)\r\n") // 471
	// + envoyer channel en arg

#define ERR_INVITEONLYCHAN(channel) (channel + " :Cannot join channel (+i)\r\n") // 473
	// + envoyer channel en arg

#define ERR_BANNEDFROMCHAN(channel) (channel + " :Cannot join channel (+b)\r\n") // 474
	// + envoyer channel en arg

#define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)\r\n") // 475
	// + envoyer channel en arg

#define ERR_BADCHANMASK(channel) (channel + " :Bad Channel Mask\r\n") // 476
	// + envoyer channel en arg

#define ERR_NOPRIVILEGES (":Permission Denied- You're not an IRC operator\r\n") // 481
// - Any command requiring operator privileges to operate
//            MUST return this error to indicate the attempt was
//            unsuccessful.

#define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator\r\n") // 482
	// + envoyer nom du channel en arg
// Any command requiring 'chanop' privileges (such as MODE messages) MUST return this error if the client
// making the attempt is not a chanop on the specified channel.

#define ERR_CANTKILLSERVER (":You can't kill a server!\r\n") // 483
// - Any attempts to use the KILL command on a server are to be refused and this error returned directly
// to the client.

#define ERR_RESTRICTED (":Your connection is restricted!\r\n") // 484
// Sent by the server to a user upon connection to indicate the restricted nature of the connection (user mode "+r").

#define ERR_NOOPERHOST (":No O-lines for your host\r\n") // 491
// If a client sends an OPER message and the server has not been configured to allow connections from the
// client's host as an operator, this error MUST be returned.


#endif


// introuvable dans la doc
// ERR_TOOMANYMATCHES 