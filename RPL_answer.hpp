#ifndef RPL_ANSWER_HPP
#define RPL_ANSWER_HPP

#include <iostream>
#include "Command/Cmd.hpp"
#include "User/User.hpp"


#define SERVERNAME "irc_dta"
#define SERVER "127.0.0.1" 
#define VERSION "1.69"
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

#define RPL_YOURHOST(localhost) (":" + localhost + " 002 :Your host is " + SERVER + ", running version" + VERSION + "\r\n") //002

#define RPL_CREATED(localhost) (":" + localhost + " 003 :This server was created " DATE "\r\n") // 003

#define RPL_MYINFO(localhost) (":" + localhost + " 004 :" SERVERNAME " " VERSION " aiwroOs OovaimnpsrtklbeI\r\n") // 004

#define QUIT(localhost, msg) (localhost + " QUIT :" + msg + "\r\n")

#define PING(localhost) (std::string("PING :") + SERVER + "\r\n")

#define PONG() (std::string("PONG :") + SERVER + "\r\n")

#define NICK(localhost, nick) (":" + localhost + " NICK " + nick + "\r\n")

#define PRIVMSG(localhost, dest, str) (":" + localhost + " PRIVMSG " + dest + " :" + str + "\r\n")

#define NOTICE(localhost, chan, str) (":" + localhost + " NOTICE " + chan + " :" + str + "\r\n")

#define PART(localhost, chan, str) (":" + localhost + " PART " + chan + " :" + str + "\r\n")

#define JOIN(localhost, chan) (":" + localhost + " JOIN " + chan + "\r\n")

#define KICK(localhost, chan, nick) (":" + localhost + " KICK " + chan + " " + nick + "\r\n")

#define RPL_AWAY(localhost, nick, msg) (":" + localhost + " 301 :" + nick + msg + "\r\n") // 301

#define RPL_UNAWAY(localhost) (":" + localhost + " 305 :You are no longer marked as being away\r\n") //305

#define RPL_NOWAWAY(localhost) (":" + localhost + " 306 :You have been marked as being away\r\n") //306

#define RPL_UMODEIS(localhost, nick, mode, param) (":" + localhost + " 221 " + nick + " :+" + mode + "" + param + " \r\n") //221

#define RPL_WHOISUSER(localhost, nick, user, host, name) (":" + localhost + " 311 : " + nick + " " + user + " " + host + " * :" + name + "\r\n") // 311

#define RPL_WHOISSERVER(localhost, nick, server_info) (":" + localhost + " 312 : " + nick + " " + SERVERNAME + " :" + server_info + "\r\n") // 312

#define RPL_WHOISOPERATOR(localhost, nick) (":" + localhost + " 313 : " + nick  + " :is an IRC operator\r\n") // 313

#define RPL_ENDOFWHO(localhost, name) (":" + localhost + " 315 : " + name + " :End of WHO list\r\n") // 315

#define RPL_WHOISIDLE(localhost, nick, integer) (":" + localhost + " 317 : " + nick + " " + integer " :seconds idle\r\n") // 317

#define RPL_ENDOFWHOIS(localhost, nick) (":" + localhost + " 318 : " + nick + " :End of WHOIS list\r\n") // 318

#define RPL_WHOISCHANNELS(localhost, nick, channel) (":" + localhost + " 319 : " + nick + " :*( ( "@" / "+" ) " + channel + " \r\n" ) // 319

#define RPL_LIST(localhost, channel, mode, topic) (":" + localhost + " 322 : " + channel + " " +  mode + " :" + topic + "\r\n") // 322

#define RPL_LISTEND(localhost) (" :End of LIST\r\n") // 323

#define RPL_CHANNELMODEIS(localhost, channel, mode) (":" + localhost + " 324 : " + channel + mode +  "-+OovaimnqpsrtklbeI\r\n") //324

#define RPL_NOTOPIC(lcalhost, channel) (":" + localhost + " 331 : " + channel + " :No topic is set") // 331

#define RPL_TOPIC(localhost, channel, topic) (":" + localhost + " 332 : " + channel + " :" + topic + "\r\n") // 332

#define RPL_INVITING(localhost, channel, nick) (":" + localhost + " 341 " + " INVITE " + nick + " " + channel + "\r\n") // 341

#define RPL_INVITELIST(localhost, channel, invitemask) (":" + localhost + " 346 : " + channel + " " + invitemask)

#define RPL_ENDOFINVITELIST(localhost, channel) (":" + localhost + " 347 : " + channel + " :End of channel invite list")

#define RPL_WHOREPLY(localhost, channel, user, host, nick, name) (":" + localhost + " 352 : " + channel + " " + user + " " + host + " " + SERVER + " " + nick + " : 0 " + name + "\r\n") // 352

#define RPL_NAMREPLY(localhost, channel, nick) (":" + localhost + " 353 : = " + channel + ": @" + nick + "\r\n" ) // 353 

#define RPL_ENDOFNAMES(localhost, nick, channel) (":" + localhost + " 366 " + nick + " " + channel + " :End of /NAMES list\r\n") // 366

#define RPL_MOTD(localhost, text) (":" + localhost + " 372 :-" + text + "\r\n") // 372

#define RPL_MOTDSTART(localhost) (":" + localhost + " 375 :- " + SERVERNAME + " Message of the day - \r\n") // 375


#define RPL_ENDOFMOTD(localhost) (":" + localhost + " 376 : End of MOTD command\r\n") // 376

#define RPL_YOUREOPER(localhost) (":" + localhost + " 381 : You are now an IRC operator\r\n") // 381

#define ERR_NOSUCHNICK(localhost, nick, channel) (":" + localhost + " 401 " + nick + " " + channel + ": No such nick/channel\r\n") // 401 nick

#define ERR_NOSUCHSERVER(localhost, serv) (":" + localhost + " 402 " + serv + " :No such server\r\n") // 402

#define ERR_NOSUCHCHANNEL(localhost, nick, channel) (":" + localhost + " 403 " + nick + " " + channel + " :No such channel\r\n") // 403

#define ERR_CANNOTSENDTOCHAN(localhost, nick, channel) (":" + localhost + " 404 " + nick + " " + channel + " :Cannot send to channel\r\n") // 404

#define ERR_TOOMANYCHANNELS(localhost, channel) (":" + localhost + " 405 " + channel + " :You have joined too many channels\r\n") // 405

#define ERR_TOOMANYTARGETS(localhost, target) (":" + localhost + " 407 " + target + " :<error code> recipients. <abort message>\r\n") // 407

#define ERR_NOORIGIN(localhost) (":" + localhost + " 409 :No origin specified") // 409

#define ERR_NORECIPIENT(localhost) (":" + localhost + " 411 : No recipient given (<command>)\r\n") // 411 

#define ERR_NOTEXTTOSEND(localhost) (":" + localhost + " 412 :No text to send\r\n") // 412

#define ERR_NOTOPLEVEL(localhost, mask) (":" + localhost + " 413 " + mask + " :No toplevel domain specified\r\n") // 413

#define ERR_WILDTOPLEVEL(localhost, mask) (":" + localhost + " 414 " + mask + " :Wildcard in toplevel domain\r\n") // 414

#define ERR_NONICKNAMEGIVEN(localhost) (":" + localhost + " 431 :No nickname given\r\n") // 431

#define ERR_ERRONEUSNICKNAME(localhost, nick) (":" + localhost + " 432 " + nick + " :Erroneous nickname\r\n") // 432

#define ERR_NICKNAMEINUSE(localhost, nick) (":" + localhost + " 433 " + nick + " " + nick + " :Nickname is already in use\r\n") // 433

#define ERR_NICKCOLLISION(localhost, nick, user, host) (":" + localhost + " 436 " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n") // 436 

#define ERR_UNAVAILRESOURCE(localhost, nick_chan) (":" + localhost + " 437 " + nick_chan + " :Nick/channel is temporarily unavailable\r\n") // 437

#define ERR_USERNOTINCHANNEL(localhost, user, nick, channel) (":" + localhost + " 441 " + user + " " + nick + " " + channel + " :They aren't on that channel\r\n") // 441

#define ERR_NOTONCHANNEL(localhost, channel) (":" + localhost + " 442 " + channel + " :You're not on that channel\r\n") // 442

#define ERR_USERONCHANNEL(localhost, user, channel) (":" + localhost + " 443 " + user + " " + channel + " :is already on channel\r\n") // 443

#define ERR_NOTREGISTERED(localhost) (":" + localhost + " 451 :You have not registered\r\n") //451

#define ERR_NEEDMOREPARAMS(localhost, key) (":" + localhost + " 461 " + key + " :Not enough parameters\r\n") // 461

#define ERR_ALREADYREGISTRED(localhost) (":" + localhost + " 462 :Unauthorized command (already registered)\r\n") // 462

#define ERR_PASSWDMISMATCH(localhost, nick) (":" + localhost + " 464 " + nick + " :Password incorrect\r\n") // 464

#define ERR_KEYSET(localhost, channel) (":" + localhost + " 467 " + channel + " :Channel key already set\r\n") // 467

#define ERR_CHANNELISFULL(localhost, channel) (":" + localhost + " 471 " + channel + " :Cannot join channel (+l)\r\n") // 471

#define ERR_INVITEONLYCHAN(localhost, channel) (":" + localhost + " 473 " + channel + " :Cannot join channel (+i)\r\n") // 473

#define ERR_BANNEDFROMCHAN(localhost, channel) (":" + localhost + " 474 " + channel + " :Cannot join channel (+b)\r\n") // 474

#define ERR_BADCHANNELKEY(localhost, channel) (":" + localhost + " 475 " + channel + " :Cannot join channel (+k)\r\n") // 475

#define ERR_BADCHANMASK(localhost, channel) (":" + localhost + " 476 " + channel + " :Bad Channel Mask\r\n") // 476

#define ERR_NOPRIVILEGES(localhost) (":" + localhost + " 481 :Permission Denied- You're not an IRC operator\r\n") // 481

#define ERR_CHANOPRIVSNEEDED(localhost, channel) (":" + localhost + " 482 " + channel + " :You're not channel operator\r\n") // 482

#define ERR_CANTKILLSERVER(localhost) (":" + localhost + " 483 :You can't kill a server!\r\n") // 483

#define ERR_RESTRICTED(localhost) (":" + localhost + " 484 :Your connection is restricted!\r\n") // 484

#define ERR_NOOPERHOST(localhost) (":" + localhost + " 491 :No O-lines for your host\r\n") // 491

#define ERR_UMODEUNKNOWNFLAG(localhost) (":" + localhost + " 501 :Unknown MODE flag\r\n") //501

#define ERR_USERSDONTMATCH(localhost, nick) (":" + localhost + " 502 " + nick + " :Cannot change mode for other users\r\n") //502

#endif