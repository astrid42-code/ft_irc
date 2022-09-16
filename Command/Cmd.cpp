#include "Cmd.hpp"



Cmd::Cmd(): _server(NULL), _user(NULL), _key(""), _size(0)
{
	// build les fcts cmds en reliant une string a la fct ou plutot faire un make_pair()?

	// basic cmds
	_cmd["NICK"] = nick;
	_cmd["USER"] = user;
	_cmd["QUIT"] = quit;
	_cmd["MODE"] = NULL;

	// channel cmds
	_cmd["JOIN"] = join;
	_cmd["PART"] = part;
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
	_cmd["PING"] = ping;
	_cmd["PONG"] = pong;
}

Cmd::Cmd(const Cmd & cp)
{
	*this = cp;
}

Cmd::~Cmd()
{
	// clear ?
	std::cout << "Command destroyed..." << std::endl;
}

Cmd & Cmd::operator=(const Cmd &cmd_op)
{
	_cmd = cmd_op._cmd;
	return (*this);
}

void Cmd::set_key(std::string key)
{
	_key = key;
}

const std::string	Cmd::get_key(void) const
{
	return (_key);
}

void Cmd::set_value(std::vector<std::string> value)
{
	_value = value;
}

std::vector<std::string>	Cmd::get_value(void) const
{
	std::cout << "get value" << std::endl;
	return (_value);
}

void	Cmd::set_size(int i)
{
	_size = i;
}

int		Cmd::get_size(void) const
{
	return (_size);
}

int		check_condition(std::string key)
{
	if (key.compare("JOIN") == 0 || key.compare("USER") == 0 || key.compare("INVITE") == 0
			|| key.compare("KICK") == 0 || key.compare("NICK") == 0 || key.compare("OPER") == 0 || key.compare("QUIT") == 0 
			|| key.compare("KILL") == 0 || key.compare("PRIVMSG") == 0 || key.compare("WHO") == 0 || key.compare("WHOIS") == 0
			|| key.compare("LIST") == 0 || key.compare("PASS") == 0 || key.compare("NAMES") == 0 || key.compare("PING") == 0
			|| key.compare("PART") == 0 /*|| key.compare("MODE") == 0*/)
		return (1);
	return (0);
}

User *Cmd::get_user_fd()
{
	std::map<int, User *> tmp = _server->get_users();
	std::map<int, User *>::iterator it = tmp.find(_sfd);

	// std::cout << "get_user_fd" << std::endl;
	// if (!_server->get_users().empty())
	// {
		// it = _server->get_users().find(_sfd);

		if (it == tmp.end())
		{
			// std::cout << "user not found" << std::endl;
			return (NULL);
		}
		else
		{
			// std::cout << "user found" << std::endl;
			return (it->second);
		}
	// }
	return (NULL);
}

void Cmd::parse_cmd(std::string str)
{
	std::string key; // pour recuperer la key (1er mot de str)
	size_t start;
	size_t end = 0;
	size_t size;
	std::string tmp_val;
	std::string	trailing;
	int tmp = 0;
	std::cout << "parse_cmd" << std::endl;
	key = str.substr(0, str.find(' '));
	size = str.size() - key.size();
	if (check_condition(key))
	{
		std::cout << "check key done" << std::endl;
		set_key(key);
		if (size == 0)
		{
			set_size(0);
			_cmd[_key](*this);
			return;
		}
		tmp_val = str.substr(str.find(' '), str.size());
		while ((start = tmp_val.find_first_not_of(' ', end)) != std::string::npos)
		{
			end = tmp_val.find(' ', start);
			if (tmp_val.find(':', start) != std::string::npos && tmp_val.find(':', start) < end)
				break ;
			_value.push_back(tmp_val.substr(start, end - start));
			std::cout << "_value" << tmp << " = " << _value[tmp] << std::endl;
			tmp++;
		}
		if (tmp_val.find(':') != std::string::npos)
		{
			trailing = tmp_val.substr(tmp_val.find(':') + 1, tmp_val.find("\r\n") - tmp_val.find(':') + 1);
			_value.push_back(trailing);
			tmp++;
			std::cout << "tvalue" << tmp << " = " << _value.back() << std::endl;
		}
		set_size(tmp);
		_cmd[_key](*this);
	}
}

void	Cmd::print(void)
{
	std::vector<std::string>::iterator it = _value.begin();

	std::cout << "key: " + _key << std::endl;
	while (it != _value.end())
	{
		std::cout << it->data() << std::endl;
		it++;
	}
	if (_user)
		_user->print();
	else
	 	std::cout << "no user" << std::endl;
	// if (_server)
	// 	std::cout << _server->print() << std::endl;
	// else
	// 	std::cout << "no server" << std::endl;
	std::cout << "end of Cmd.print()" << std::endl;
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