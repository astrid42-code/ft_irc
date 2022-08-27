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

// void   create_map() {
// 	void *ptr[] () = {
//     &test, &ft_join
// };

int Cmd::exec_cmd(std::string key)
{
	if (key == "" || key != "JOIN" || key != "USER" || key != "INVITE" || key != "KICK" || key != "NICK" || key != "OPER" || key != "QUIT" 
			|| key != "KILL" || key != "PRIVMSG" || key != "WHO" || key != "WHOIS")
		return (1);
	_cmd[key](com_str);
	std::cout << "str_cmd = " << com_str.str_cmd << '\n';
	return (1);
}

// void parse_cmd(std::string str){
// 	std::string key; // va recuperer la key (1er mot de str)
// 	int result;

// 	for (int i = 0; str[i] != " "; i++)
// 		result = i;
// 	key = str.substr(0, result);
// 	if (key != "JOIN" || key != "USER" || key != "INVITE" || key != "KICK" || key != "NICK" || key != "OPER" || key != "QUIT" 
// 			|| key != "KILL" || key != "PRIVMSG" || key != "WHO" || key != "WHOIS")
// 			return ;
	
// }


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