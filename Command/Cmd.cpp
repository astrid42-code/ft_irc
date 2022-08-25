#include "Cmd.hpp"



Cmd::Cmd(){
	// build les fcts cmds en reliant une string a la fct 
	_cmd["TEST"] = test; // a retirer quand le test pour utiliser le ptr sur fct marche
	// _cmd["JOIN"] = ft_join;
	// _cmd["USER"] = ft_user;
	// _cmd["INVITE"] = ft_invite;
	// _cmd["KICK"] = ft_kick;
	// _cmd["NICK"] = ft_nick;
	// _cmd["OPER"] = ft_oper;
	// _cmd["QUIT"] = ft_kick;
	// _cmd["USER"] = ft_user;
	// _cmd["KILL"] = ft_kill;
	// _cmd["PRIVMSG"] = ft_privmsg;
	// _cmd["WHO"] = ft_who;
	// _cmd["WHOIS"] = ft_whois;

	std::cout << "blabla" << '\n';
}

Cmd::Cmd(const Cmd & cp){
	*this = cp;
}

Cmd::~Cmd(){
	std::cout << "bye" << '\n';
}

// void   create_map() {
// 	void *ptr[] () = {
//     &test, &ft_join
// };

int Cmd::ex_cmd(std::string key)
{

	_cmd[key](com_str);
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