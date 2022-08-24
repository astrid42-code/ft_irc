#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include <map>
#include <vector>

class Cmd{

	public:
		Cmd();
		Cmd(const Cmd & cp);
		~Cmd();

		// struct contenant les elements utiles au parsing
		typedef struct Command{
			std::string					str_cmd; // la string du 1er element recu (la key de ma map)
			std::vector<std::string>	args; // les args apres la commande (en vector pour en recevoir plsrs si necessaire)
		}				Command;

		// ptr sur fonction des cmds qui prend une ref sur ma struct Command
		typedef void (*ptr_ft)(Command & command);
    
	private:
    	std::map<std::string, ptr_ft>	_cmd;
};

//parametre : ref sur la struct avec les donnees utiles a utiliser pour les cds (args, )
void test(Cmd::Command & command);
// void ft_join(Cmd::Command & command);
// void ft_user(Cmd::Command & command);
// void ft_invite(Cmd::Command & command);
// void ft_kick(Cmd::Command & command);
// void ft_nick(Cmd::Command & command);
// void ft_oper(Cmd::Command & command);
// void ft_kick(Cmd::Command & command);
// void ft_user(Cmd::Command & command);
// void ft_kill(Cmd::Command & command);
// void ft_privmsg(Cmd::Command & command);
// void ft_who(Cmd::Command & command);
// void ft_whois(Cmd::Command & command);

#endif