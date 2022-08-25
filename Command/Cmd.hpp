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
		typedef struct Command{
			std::string					str_cmd; // la string du 1er element recu (la key de ma map)
			std::vector<std::string>	args; // les args apres la commande (en vector pour en recevoir plsrs si necessaire)
		} Command;
		Command com_str;
		// struct contenant les elements utiles au parsing
		

		// ptr sur fonction des cmds qui prend une ref sur ma struct Command
		typedef void (*ptr_ft)(Command & command);
		std::map<std::string, ptr_ft>::iterator	it;

		
    
	private:
    	std::map<std::string, ptr_ft>	_cmd;
};

//parametre : ref sur la struct avec les donnees utiles a utiliser pour les cds (args, )
		void test(Cmd::Command & command);
		void ft_join(Cmd::Command & command);
=======
void test(Cmd::Command & command);//Cmd::Command & command
