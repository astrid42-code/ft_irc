#ifndef RPL_ANSWER_HPP
#define RPL_ANSWER_HPP

#include <iostream>
#include "Command/Cmd.hpp"
#include "User/User.hpp"


#define SERVERNAME "irc_dta"
#define SERVER "127.0.0.1"  // adresse ip ex : Your host is 62.210.33.192, running version 1.69
#define VERSION "1.69" // version actuelle a verifier
#define DATE "Mon Aug 25 16:57:33 2022"
#define DEFAULT_NAME "toto"
#define TIME_LIMIT 60

#define AWAY_DEFAULT (":You have been marked as being away")

#define PINGU ("\n\
dHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHb \n\
HHP%%#%%%%%%%%%%%%%%%%#%%%%%%%#%%VHH \n\
HH%%%%%%%%%%#%v~~~~~~\\%%%#%%%%%%%%HH \n\
HH%%%%%#%%%%v'        ~~~~\\%%%%%#%HH \n\
HH%%#%%%%%%v'dHHb      a%%%#%%%%%%HH \n\
HH%%%%%#%%v'dHHHA     :%%%%%%#%%%%HH \n\
HH%%%#%%%v' VHHHHaadHHb:%#%%%%%%%%HH \n\
HH%%%%%#v'   `VHHHHHHHHb:%%%%%#%%%HH \n\
HH%#%%%v'      `VHHHHHHH:%%%#%%#%%HH \n\
HH%%%%%'        dHHHHHHH:%%#%%%%%%HH \n\
HH%%#%%        dHHHHHHHH:%%%%%%#%%HH \n\
HH%%%%%       dHHHHHHHHH:%%#%%%%%%HH \n\
HH#%%%%       VHHHHHHHHH:%%%%%#%%%HH \n\
HH%%%%#   b    HHHHHHHHV:%%%#%%%%#HH \n\
HH%%%%%   Hb   HHHHHHHV'%%%%%%%%%%HH \n\
HH%%#%%   HH  dHHHHHHV'%%%#%%%%%%%HH \n\
HH%#%%%   VHbdHHHHHHV'#%%%%%%%%#%%HH \n\
HHb%%#%    VHHHHHHHV'%%%%%#%%#%%%%HH \n\
HHHHHHHb    VHHHHHHH:%odHHHHHHbo%dHH \n\
HHHHHHHHboodboonkoodHHHHHHHHHHHHHHHH \n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH \n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH \n\
VHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHGGN94\r\n")

#define RPL_WELCOME(localhost, nick) (":" + localhost + " 001 " + nick + " :Welcome to the Internet Relay Network " + localhost + "\r\n") //001
// #define RPL_WELCOME(nick, user, host) (nick + "!" + user + "@" + host + " 001 " + nick + " :Welcome to the Internet Relay Network\r\n") //001
        	// + envoyer <nick>!<user>@<host>) en arguments
			// + ajouter dessin?

#define RPL_YOURHOST(localhost) (":" + localhost + " 002 :Your host is " + SERVER + ", running version" + VERSION + "\r\n") //002

#define RPL_CREATED(localhost) (":" + localhost + " 003 :This server was created " DATE "\r\n") // 003

#define RPL_MYINFO(localhost) (":" + localhost + " 004 :" SERVERNAME " " VERSION " aiwroOs OovaimnpsrtklbeI\r\n") // 004
	// + envoyer nombre de users en fct de leur mode (nbr de users connectes, nbre d'invisible users connectes)
	// (prevoir fcts dans class users pour comptabiliser les users co en fct de leurs statuts, a envoyer en arguments)
	//  et channels avalaible en arg

#define QUIT(localhost, msg) (localhost + " QUIT :" + msg + "\r\n")

#define PING(localhost) (std::string("PING :") + SERVER + "\r\n")

#define PONG() (std::string("PONG :") + SERVER + "\r\n")

#define NICK(localhost, nick) (":" + localhost + " NICK " + nick + "\r\n")

#define PRIVMSG(localhost, chan, str) (":" + localhost + " PRIVMSG " + chan + " :" + str + "\r\n")

#define NOTICE(localhost, chan, str) (":" + localhost + " NOTICE " + chan + " :" + str + "\r\n")

#define PART(localhost, chan, str) (":" + localhost + " PART " + chan + " :" + str + "\r\n")

#define JOIN(localhost, chan) (":" + localhost + " JOIN " + chan + "\r\n")

#define KICK(localhost, chan, nick) (":" + localhost + " KICK " + chan + " " + nick + "\r\n")

#define RPL_AWAY(localhost, nick, msg) (":" + localhost + " 301 " + nick + msg + "\r\n") // 301
	// + envoyer nick du user en arg

#define RPL_UNAWAY(localhost) (":" + localhost + " 305 :You are no longer marked as being away\r\n") //305

#define RPL_NOWAWAY(localhost) (":" + localhost + " 306 :You have been marked as being away\r\n") //306

#define RPL_UMODEIS(localhost, nick, mode, param) (":" + localhost + " 221 " + nick + " :+" + mode + "" + param + " \r\n") //221 
	// To answer a query about a client's own mode, RPL_UMODEIS is sent back. 

#define RPL_WHOISUSER(localhost, nick, user, host, name) (":" + localhost + " 311 " + nick + " " + user + " " + host + " * :" + name + "\r\n") // 311
	// + envoyer nick du user, user (?), host et real name en arg

#define RPL_WHOISSERVER(localhost, nick, server_info) (":" + localhost + " 312 : " + nick + " " + SERVERNAME + " :" + server_info + "\r\n") // 312
	// + envoyer nick du user et server info (?)

#define RPL_WHOISOPERATOR(localhost, nick) (":" + localhost + " 313 : " + nick  + " :is an IRC operator\r\n") // 313

#define RPL_ENDOFWHO(localhost, name) (":" + localhost + " 315 : " + name + " :End of WHO list\r\n") // mode_params 315
	// + envoyer nick (?) du user en arg
// - The RPL_WHOREPLY and RPL_ENDOFWHO pair are used to answer a WHO message.  The RPL_WHOREPLY is only
// sent if there is an appropriate match to the WHO query.  If there is a list of parameters supplied
// with a WHO message, a RPL_ENDOFWHO MUST be sent after processing each list item with <name> being the item.

#define RPL_WHOISIDLE(localhost, nick, integer) (":" + localhost + " 317 : " + nick + " " + integer " :seconds idle\r\n") // 317
	// + envoyer nick et integer(??)

#define RPL_ENDOFWHOIS(localhost, nick) (":" + localhost + " 318 : " + nick + " :End of WHOIS list\r\n") // 318

#define RPL_WHOISCHANNELS(localhost, nick, channel) (":" + localhost + " 319 : " + nick + " :*( ( "@" / "+" ) " + channel + " \r\n" ) // 319 (verifier syntaxe du msg)
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

#define RPL_LIST(localhost, channel, mode, topic) (":" + localhost + " 322 : " + channel + " " +  mode + " :" + topic + "\r\n") // 322
	// + envoyer channel, mode visible (?) et topic (sujet du chan) en arg

#define RPL_LISTEND(localhost) (" :End of LIST\r\n") // 323
//  - Replies RPL_LIST, RPL_LISTEND mark the actual replies
//    with data and end of the server's response to a LIST
//    command.  If there are no channels available to return,
//    only the end reply MUST be sent.

#define RPL_CHANNELMODEIS(localhost, channel, mode) (":" + localhost + " 324 : " + channel + mode +  "-+OovaimnqpsrtklbeI\r\n") //324

#define RPL_NOTOPIC(lcalhost, channel) (":" + localhost + " 331 : " + channel + " :No topic is set") // 331

#define RPL_TOPIC(localhost, channel, topic) (":" + localhost + " 332 : " + channel + " :" + topic + "\r\n") // 332
	// + envoyer channel et topic (sujet du chan) en arg
// When sending a TOPIC message to determine the channel topic, one of two replies is sent.  If
// the topic is set, RPL_TOPIC is sent back else RPL_NOTOPIC.

#define RPL_INVITING(localhost, channel, nick) (":" + localhost + " 341 " + " INVITE " + nick + " " + channel + "\r\n") // 341
	// + envoyer channel et nick du user en arg
// Returned by the server to indicate that the attempted INVITE message was successful and is
// being passed onto the end client.

#define RPL_INVITELIST(localhost, channel, invitemask) (":" + localhost + " 346 : " + channel + " " + invitemask)

#define RPL_ENDOFINVITELIST(localhost, channel) (":" + localhost + " 347 : " + channel + " :End of channel invite list")



#define RPL_WHOREPLY(localhost, channel, user, host, nick, name) (":" + localhost + " 352 : " + channel + " " + user + " " + host + " " + SERVER + " " + nick + " : 0 " + name + "\r\n") // 352
	// envoyer les args

#define RPL_NAMREPLY(localhost, channel, nick) (":" + localhost + " 353 : = " + channel + ": @" + nick + "\r\n" ) // 353 + " :" + nicks??
	// + envoyer channel et nick du user en arg
//  - "@" is used for secret channels, "*" for private
//    channels, and "=" for others (public channels).

#define RPL_ENDOFNAMES(localhost, nick, channel) (":" + localhost + " 366 " + nick + " " + channel + " :End of /NAMES list\r\n") // 366
	// + envoyer channel en arg
// To reply to a NAMES message, a reply pair consisting
//            of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
//            server back to the client.  If there is no channel
//            found as in the query, then only RPL_ENDOFNAMES is

#define RPL_MOTDSTART(localhost) (":" + localhost + " 375 :- " + SERVERNAME + " Message of the day - \r\n") // 375

#define RPL_MOTD(localhost, text) (":" + localhost + " 372 :-" + text + "\r\n") //std::string(" :- ") 

#define RPL_ENDOFMOTD(localhost) (":" + localhost + " 376 : End of MOTD command\r\n") // 376

#define RPL_YOUREOPER(localhost) (":" + localhost + " 381 : You are now an IRC operator\r\n") // 381
// RPL_YOUREOPER is sent back to a client which has just successfully issued an OPER message and gained operator status.

#define ERR_NOSUCHNICK(localhost, nick, channel) (":" + localhost + " 401 " + nick + " " + channel + ": No such nick/channel\r\n") // 401 nick
	// + envoyer nick du user en arg
// Used to indicate the nickname parameter supplied to a command is currently unused.

#define ERR_NOSUCHSERVER(localhost, serv) (":" + localhost + " 402 " + serv + " :No such server\r\n") // 402
// - Used to indicate the server name given currently does not exist.

#define ERR_NOSUCHCHANNEL(localhost, nick, channel) (":" + localhost + " 403 " + nick + " " + channel + " :No such channel\r\n") // 403
// #define ERR_NOSUCHCHANNEL(localhost, nick, channel) (":" + localhost + " 403 " + nick + " : " + channel + " :No such channel\r\n") // 403
	// + envoyer channel name en arg
// Used to indicate the given channel name is invalid.

#define ERR_CANNOTSENDTOCHAN(localhost, nick, channel) (":" + localhost + " 404 " + nick + " " + channel + " :Cannot send to channel\r\n") // 404
	// + envoyer channel name en arg
// - Sent to a user who is either (a) not on a channel which is mode +n or (b) not a chanop (or mode +v) on
//  a channel which has mode +m set or where the user is
//  banned and is trying to send a PRIVMSG message to that channel.


#define ERR_TOOMANYCHANNELS(localhost, channel) (":" + localhost + " 405 " + channel + " :You have joined too many channels\r\n") // 405
	// + envoyer channel name en arg
// - Sent to a user when they have joined the maximum number of allowed channels and they try to join
// another channel.

#define ERR_TOOMANYTARGETS(localhost, target) (":" + localhost + " 407 " + target + " :<error code> recipients. <abort message>\r\n") // 407
	// + envoyer target (user?) en arg
//  - Returned to a client which is attempting to send a
//    PRIVMSG/NOTICE using the user@host destination format
//    and for a user@host which has several occurrences.

//  - Returned to a client which trying to send a
//    PRIVMSG/NOTICE to too many recipients.

//  - Returned to a client which is attempting to JOIN a safe
//    channel using the shortname when there are more than one
//    such channel.

#define ERR_NOORIGIN(localhost) (":" + localhost + " 409 :No origin specified") // 409
// - PING or PONG message missing the originator parameter.

#define ERR_NORECIPIENT(localhost) (":" + localhost + " 411 : No recipient given (<command>)\r\n") // 411 

#define ERR_NOTEXTTOSEND(localhost) (":" + localhost + " 412 :No text to send\r\n") // 412

#define ERR_NOTOPLEVEL(localhost, mask) (":" + localhost + " 413 " + mask + " :No toplevel domain specified\r\n") // 413

#define ERR_WILDTOPLEVEL(localhost, mask) (":" + localhost + " 414 " + mask + " :Wildcard in toplevel domain\r\n") // 414

#define ERR_NONICKNAMEGIVEN(localhost) (":" + localhost + " 431 :No nickname given\r\n") // 431
// - Returned when a nickname parameter expected for a command and isn't found.

#define ERR_ERRONEUSNICKNAME(localhost, nick) (":" + localhost + " 432 " + nick + " :Erroneous nickname\r\n") // 432
	// + envoyer nick en arg
// - Returned after receiving a NICK message which contains
//            characters which do not fall in the defined set.  See
//            section 2.3.1 for details on valid nicknames.

#define ERR_NICKNAMEINUSE(localhost, nick) (":" + localhost + " 433 " + nick + " " + nick + " :Nickname is already in use\r\n") // 433
	// + envoyer nick en arg
// - Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.

#define ERR_NICKCOLLISION(localhost, nick, user, host) (":" + localhost + " 436 " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n") // 436 
	// + envoyer nick, user (nom dans l'email?) et host (fin adresse mail ?) en arg
// - Returned by a server to a client when it detects a nickname collision (registered of a NICK that
// already exists by another server).

#define ERR_UNAVAILRESOURCE(localhost, nick_chan) (":" + localhost + " 437 " + nick_chan + " :Nick/channel is temporarily unavailable\r\n") // 437
// + envoyer channel ou nick en arg
// - Returned by a server to a user trying to join a channel
//            currently blocked by the channel delay mechanism.

// - Returned by a server to a user trying to change nickname
//            when the desired nickname is blocked by the nick delay
//            mechanism.

#define ERR_USERNOTINCHANNEL(localhost, user, nick, channel) (":" + localhost + " 441 " + user + " " + nick + " " + channel + " :They aren't on that channel\r\n") // 441
	// + envoyer user et channel en arg
// - Returned by the server to indicate that the target user of the command is not on the given channel.

#define ERR_NOTONCHANNEL(localhost, channel) (":" + localhost + " 442 " + channel + " :You're not on that channel\r\n") // 442
	// + envoyer nom du channel en arg
// Returned by the server whenever a client tries to perform a channel affecting command for which the
// client isn't a member.

#define ERR_USERONCHANNEL(localhost, user, channel) (":" + localhost + " 443 " + user + " " + channel + " :is already on channel\r\n") // 443
	// + envoyer user et channel en arg
// Returned when a client tries to invite a user to a channel they are already on.

#define ERR_NOTREGISTERED(localhost) (":" + localhost + " 451 :You have not registered\r\n") //451
// Returned by the server to indicate that the client MUST be registered before the server will allow it
// to be parsed in detail.

#define ERR_NEEDMOREPARAMS(localhost, key) (":" + localhost + " 461 " + key + " :Not enough parameters\r\n") // 461
	// + envoyer key (nom de cmd) en arg
// Returned by the server by numerous commands to indicate to the client that it didn't supply enough parameters.

#define ERR_ALREADYREGISTRED(localhost) (":" + localhost + " 462 :Unauthorized command (already registered)\r\n") // 462
// Returned by the server to any link which tries to change part of the registered details (such as
// password or user details from second USER message).

#define ERR_PASSWDMISMATCH(localhost, nick) (":" + localhost + " 464 " + nick + " :Password incorrect\r\n") // 464
// Returned to indicate a failed attempt at registering a connection for which a password was required and
// was either not given or incorrect.

#define ERR_KEYSET(localhost, channel) (":" + localhost + " 467 " + channel + " :Channel key already set\r\n") // 467

#define ERR_CHANNELISFULL(localhost, channel) (":" + localhost + " 471 " + channel + " :Cannot join channel (+l)\r\n") // 471
	// + envoyer channel en arg

#define ERR_INVITEONLYCHAN(localhost, channel) (":" + localhost + " 473 " + channel + " :Cannot join channel (+i)\r\n") // 473
	// + envoyer channel en arg

#define ERR_BANNEDFROMCHAN(localhost, channel) (":" + localhost + " 474 " + channel + " :Cannot join channel (+b)\r\n") // 474
	// + envoyer channel en arg

#define ERR_BADCHANNELKEY(localhost, channel) (":" + localhost + " 475 " + channel + " :Cannot join channel (+k)\r\n") // 475
	// + envoyer channel en arg

#define ERR_BADCHANMASK(localhost, channel) (":" + localhost + " 476 " + channel + " :Bad Channel Mask\r\n") // 476
	// + envoyer channel en arg

#define ERR_NOPRIVILEGES(localhost) (":" + localhost + " 481 :Permission Denied- You're not an IRC operator\r\n") // 481
// - Any command requiring operator privileges to operate
//            MUST return this error to indicate the attempt was
//            unsuccessful.

#define ERR_CHANOPRIVSNEEDED(localhost, channel) (":" + localhost + " 482 " + channel + " :You're not channel operator\r\n") // 482
	// + envoyer nom du channel en arg
// Any command requiring 'chanop' privileges (such as MODE messages) MUST return this error if the client
// making the attempt is not a chanop on the specified channel.

#define ERR_CANTKILLSERVER(localhost) (":" + localhost + " 483 :You can't kill a server!\r\n") // 483
// - Any attempts to use the KILL command on a server are to be refused and this error returned directly
// to the client.

#define ERR_RESTRICTED(localhost) (":" + localhost + " 484 :Your connection is restricted!\r\n") // 484
// Sent by the server to a user upon connection to indicate the restricted nature of the connection (user mode "+r").

#define ERR_NOOPERHOST(localhost) (":" + localhost + " 491 :No O-lines for your host\r\n") // 491
// If a client sends an OPER message and the server has not been configured to allow connections from the
// client's host as an operator, this error MUST be returned.

#define ERR_UMODEUNKNOWNFLAG(localhost) (":" + localhost + " 501 :Unknown MODE flag\r\n") //501
// Returned by the server to indicate that a MODE message was sent with a nickname parameter and that
// the a mode flag sent was not recognized. 

#define ERR_USERSDONTMATCH(localhost, nick) (":" + localhost + " 502 " + nick + " :Cannot change mode for other users\r\n") //502
//Error sent to any user trying to view or change the user mode for a user other than themselves. 

#endif


// introuvable dans la doc
// ERR_TOOMANYMATCHES 