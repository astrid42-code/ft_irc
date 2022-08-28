#include "Cmd.hpp"



Cmd::Cmd(){
	// build les fcts cmds en reliant une string a la fct 

	_cmd["JOIN"] = join;
	_cmd["USER"] = user;
	_cmd["INVITE"] = invite;
	_cmd["KICK"] = kick;
	_cmd["NICK"] = nick;
	_cmd["OPER"] = oper;
	_cmd["QUIT"] = kick;
	_cmd["KILL"] = kill;
	_cmd["PRIVMSG"] = privmsg;
	_cmd["WHO"] = who;
	_cmd["WHOIS"] = whois;
	
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

int Cmd::exec_cmd(std::string key)
{
	// if (key.compare("JOIN") == 0 || key.compare("USER") == 0 || key.compare("INVITE") == 0 || key.compare("KICK") == 0 || key.compare("NICK") == 0 || key.compare("OPER") == 0 || key.compare("QUIT") == 0 
	// 		|| key.compare("KILL") == 0 || key.compare("PRIVMSG") == 0 || key.compare("WHO") == 0 || key.compare("WHOIS") == 0){
	// 		_cmd[key](com_str);
	// 		// et continuer le parsing 
	// 		return (0);
	// 	}
	(void)key;
	std::cout << "prout2 " << "_key = " << com_str._key << '\n';
	return (1);
}

void Cmd::parse_cmd(std::string const str){ 
	std::string key; // pour recuperer la key (1er mot de str)
	int result;

	for (int i = 0; str[i] != ' '; i++)
		result = i;
	key = str.substr(0, result);
	if (key.compare("JOIN") == 0 || key.compare("USER") == 0 || key.compare("INVITE") == 0 || key.compare("KICK") == 0 || key.compare("NICK") == 0 || key.compare("OPER") == 0 || key.compare("QUIT") == 0 
			|| key.compare("KILL") == 0 || key.compare("PRIVMSG") == 0 || key.compare("WHO") == 0 || key.compare("WHOIS") == 0) {
			set_key(key);
			com_str._key = get_key();
		}
}


//autres cmds possibles?
// - LIST
// - NAMES
// - PART
// - TOPIC
// - MODE
// - PING
// - PONG
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