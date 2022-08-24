#include "Cmd.hpp"

Cmd::Cmd(){
	// build les fcts cmds en reliant une string a la fct 
	_cmd["TEST"] = test; // a retirer quand le test pour utiliser le ptr sur fct marche
	_cmd["JOIN"] = ft_join;
	_cmd["USER"] = ft_user;
	_cmd["INVITE"] = ft_invite;
	_cmd["KICK"] = ft_kick;
	_cmd["NICK"] = ft_nick;
	_cmd["OPER"] = ft_oper;
	_cmd["QUIT"] = ft_kick;
	_cmd["USER"] = ft_user;
	_cmd["KILL"] = ft_kill;
	_cmd["PRIVMSG"] = ft_privmsg;
	_cmd["WHO"] = ft_who;
	_cmd["WHOIS"] = ft_whois;
}

Cmd::Cmd(const Cmd & cp){
	*this = cp;
}

Cmd::~Cmd(){}

// void   ft_cmd() {
// 	void *ptr[] () = {
//     &test, &ft_join
// };


// fcts a faire ensuite

void test(void){
    std::cout << "blabla test" << '\n';
}

void join(){
    std::cout << "join test" << '\n';
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