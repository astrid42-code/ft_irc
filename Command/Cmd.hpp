#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include <map>
#include <vector>
#include <iterator>


class Cmd{

	public:
		Cmd();
		Cmd(const Cmd & cp);
		~Cmd();

		Cmd & operator=(const Cmd & cmd_op);

		// struct contenant les elements utiles au parsing
		typedef struct Command{
			std::string					_key; // la string du 1er element recu (la key de ma map)
			std::vector<std::string>	_value; // les args apres la commande (en vector pour en recevoir plsrs si necessaire)
		} Command;
		Command com_str;
		

		// ptr sur fonction des cmds qui prend une ref sur ma struct Command
		typedef void (*ptr_ft)(Command & command);
		std::map<std::string, ptr_ft>::iterator	it;

		void set_key(std::string key) ;
		const std::string &	get_key(void) const;

		int exec_cmd(std::string key);
		std::string parse_cmd(std::string str);
    
	private:
    	std::map<std::string, ptr_ft>	_cmd;
};

//parametre : ref sur la struct avec les donnees utiles a utiliser pour les cds (_value/args, )
void join(Cmd::Command & command);
void user(Cmd::Command & command);
void invite(Cmd::Command & command);
void kick(Cmd::Command & command);
void nick(Cmd::Command & command);
void oper(Cmd::Command & command);
void quit(Cmd::Command & command);
void kill(Cmd::Command & command);
void privmsg(Cmd::Command & command);
void who(Cmd::Command & command);
void whois(Cmd::Command & command);

#endif