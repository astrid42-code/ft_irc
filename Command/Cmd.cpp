#include "Cmd.hpp"



Cmd::Cmd(){
	// build les fcts cmds en reliant une string a la fct 

// ou plutot faire un make_pair()?

	// basic cmds
	_cmd["NICK"] = nick;
	_cmd["USER"] = user;
	_cmd["QUIT"] = quit;

	// channel cmds
	_cmd["JOIN"] = join;
	// _cmd["PART"] = part; // non obligatoire?
	_cmd["LIST"] = list;

	// advanced cmds
	_cmd["PRIVMSG"] = privmsg;
	_cmd["WHO"] = who;

	_cmd["INVITE"] = invite;
	_cmd["KICK"] = kick;
	_cmd["OPER"] = oper;
	_cmd["KILL"] = kill;
	_cmd["WHOIS"] = whois;
	_cmd["PASS"] = pass;
	
}

Cmd::Cmd(const Cmd & cp){
	*this = cp;
}

Cmd::~Cmd(){
	// std::cout << "bye" << '\n';
}

Cmd & Cmd::operator=(const Cmd & cmd_op){
	_cmd = cmd_op._cmd;
	return (*this);
}
// void   create_map() {
// 	void *ptr[] () = {
//     &test, &ft_join
// };

void Cmd::set_key(std::string key) {
	com_str._key = key;
}

const std::string&	Cmd::get_key(void) const{
	return (com_str._key);
}

// void Cmd::set_value(std::string value) {
// 	com_str._value = value;
// }

// const std::string&	Cmd::get_value(void) const{
// 	return (com_str._value);
// }

int Cmd::exec_cmd(std::string key)
{

	_cmd[key](com_str);
	// std::cout << "prout2 " << "_key = " << com_str._key << '\n';
	return (1);
}

void Cmd::parse_cmd(std::string const str){ 
	std::string key; // pour recuperer la key (1er mot de str)
	int result;
	size_t start;
	size_t end = 0;
	std::string tmp_val;
	int i = 0;

	for (int i = 0; str[i] != ' '; i++)
		result = i;
	key = str.substr(0, result + 1);
//	std::cout << "key = " << key << "cmp = " << key.compare(key) << '\n';
	if (key.compare("JOIN") == 0 || key.compare("USER") == 0 || key.compare("INVITE") == 0
			|| key.compare("KICK") == 0 || key.compare("NICK") == 0 || key.compare("OPER") == 0 || key.compare("QUIT") == 0 
			|| key.compare("KILL") == 0 || key.compare("PRIVMSG") == 0 || key.compare("WHO") == 0 || key.compare("WHOIS") == 0
			|| key.compare("LIST") == 0 || key.compare("PASS") == 0 || key.compare("NAMES") == 0) {
			set_key(key);
			com_str._key = get_key();
			tmp_val = str.substr(result + 1, str.size());
			while ((start = tmp_val.find_first_not_of(' ', end)) != std::string::npos){
				end = tmp_val.find(' ', start);
				com_str._value.push_back(tmp_val.substr(start, end - start));
				std::cout << "value = " << com_str._value[i] << '\n';
				i++;
			}
			exec_cmd(com_str._key);
		}
		else
			return;

/*	
a revoir : exception caught + abort
// comment récuperer et lancer la fct? a t on besoin d'un it ici?
	it = _cmd.find(com_str._key);
	if (it != _cmd.end()) { // sauf pour exit et autres fcts speciales
	}
*/
}


//autres cmds possibles?
// - PART
// Paramètres : <nom du chan> [<commentaire>]
// Réponses possibles : ERR_NEEDMOREPARAMS (461), ERR_NOSUCHCHANNEL (403), ERR_NOTONCHANNEL (442)

// Ce message permet de sortir d'un chan. 
// - TOPIC
// - MODE
// 1 Message MODE (gestion des chans et des users dans le chan)
// Paramètres : <nom du chan> <+|-|o|p|s|i|t|n|b|v|m>+ <autres paramètres>
// Réponses possibles : ERR_NEEDMOREPARAMS (461), ERR_NOSUCHCHANNEL (403), ERR_NOTONCHANNEL (442), ERR_NOSUCHNICK (401), ERR_CHANOPRIVSNEEDED (482), RPL_CHANNELMODEIS (324), ERR_KEYSET (467), RPL_BANLIST (367), RPL_ENDOFBANLIST (368), ERR_UNKNOWNMODE (472)

// Ce message permet aux ops de modifier la configuration du chan.
// o : ajoute ou enlève le statut d'opérateur à un membre du chan.
// v : ajoute ou enlève le voice à un membre du chan (autorisation d'envoyer des messages au chan en état de modération).
// b : ajoute ou enlève un ban (interdiction d'entrer sur le chan).

// l : ajoute (éventuellement modifie) ou enlève le nombre maximum d'utilisateurs pouvant entrer sur le chan.
// k : ajoute (éventuellement modifie) ou enlève la clé du chan.
// t : interdit aux non-chanops de modifier le topic du chan.
// i : interdit l'entrée sur le chan aux non-invités.
// m : interdit aux non-voices de parler sur le chan (modération du chan).
// n : interdit les messages venant de personnes n'étant pas sur le chan.
// s : Chan secret (n'apparait pas dans les listings à moins que l'utilisateur ne soit présent sur le chan).
// p : Chan privé (ne divulgue pas d'informations autres que l'existence du chan dans les listings à moins que l'utilisateur ne soit présent sur le chan).

// 2 Message MODE (gestion des utilisateurs)
// Paramètres : <nick> <+|-|o|i>+
// Réponses possibles : ERR_NEEDMOREPARAMS (461), ERR_USERSDONTMATCH (502), ERR_UMODEUNKNOWNFLAG (501), RPL_UMODEIS (221)

// Ce message permet d'attribuer certains pouvoirs à certains utilisateurs.
// o : ajoute ou enlève le statut d'IRCOP.
// i : ajoute ou enlève le statut invisible (informations réduites dans le WHOIS). 

// voir egalement section 3.1 du rfc 2812

// - PING


//       Command: PING
//    Parameters: <server1> [ <server2> ]

//    The PING command is used to test the presence of an active client or
//    server at the other end of the connection.  Servers send a PING
//    message at regular intervals if no other activity detected coming
//    from a connection.  If a connection fails to respond to a PING
//    message within a set amount of time, that connection is closed.  A
//    PING message MAY be sent even if the connection is active.

//    When a PING message is received, the appropriate PONG message MUST be
//    sent as reply to <server1> (server which sent the PING message out)
//    as soon as possible.  If the <server2> parameter is specified, it
//    represents the target of the ping, and the message gets forwarded
//    there.

//    Numeric Replies:

//            ERR_NOORIGIN                  ERR_NOSUCHSERVER

//    Examples:

//    PING tolsun.oulu.fi             ; Command to send a PING message to
//                                    server

//    PING WiZ tolsun.oulu.fi         ; Command from WiZ to send a PING
//                                    message to server "tolsun.oulu.fi"

//    PING :irc.funet.fi              ; Ping message sent by server
//                                    "irc.funet.fi"

// - PONG

//       Command: PONG
//    Parameters: <server> [ <server2> ]

//    PONG message is a reply to ping message.  If parameter <server2> is
//    given, this message MUST be forwarded to given target.  The <server>
//    parameter is the name of the entity who has responded to PING message
//    and generated this message.

//    Numeric Replies:

//            ERR_NOORIGIN                  ERR_NOSUCHSERVER

//    Example:

//    PONG csd.bu.edu tolsun.oulu.fi  ; PONG message from csd.bu.edu to
//                                    tolsun.oulu.fi

// - AWAY
// - ISON
// - USERHOST
// - USERS (handled but disabled)
// - WALLOPS
// - NOTICE
// - 
// - ADMIN
// - INFO
// - LUSERS
// - MOTD
// - TIME
// - VERSION
// - WHOWAS


// https://mathieu-lemoine.developpez.com/tutoriels/irc/protocole/?page=page-4