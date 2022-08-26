#include "Cmd.hpp"



Cmd::Cmd(){
	// build les fcts cmds en reliant une string a la fct 
	_cmd["TEST"] = test; // a retirer quand le test pour utiliser le ptr sur fct marche
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
	_cmd[key](com_str);
	std::cout << "str_cmd = " << com_str.str_cmd << '\n';
	return (1);
}

// fcts a faire ensuite

void test(Cmd::Command &command){ 
    std::cout << "blabla test" << '\n';
	std::cout << command.str_cmd << std::endl;
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