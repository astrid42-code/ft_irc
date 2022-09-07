#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include "../User/User.hpp"
#include "../Server/Server.hpp"
#include "RPL_answer.hpp"

class User;

class Server;

class Cmd
{

	public:
		Cmd();
		Cmd(const Cmd & cp);
		~Cmd();

		Cmd & operator=(const Cmd & cmd_op);
		
		// struct contenant les elements utiles au parsing
		typedef struct Command
		{
			std::string					_key; // la string du 1er element recu (la key de ma map)
			std::vector<std::string>	_value; // les args apres la commande (en vector pour en recevoir plsrs si necessaire)
			// int							_err;
			User					*_user; // recuperer les infos d'un user (nick, pwd, ...) 
			// pour checker les erreurs (ex nick already registered), ou envoyer des msgs, ...
			Server					*_server;
		} Command;

		Command command;

		// ptr sur fonction des cmds qui prend une ref sur ma struct Command
		typedef void (*ptr_ft)(Command & command);
		std::map<std::string, ptr_ft>::iterator	it;

		void set_key(std::string key) ;
		const std::string &	get_key(void) const;
	//	void set_value(std::string value);
	//	const std::string &	get_value(void) const;

		int exec_cmd(std::string key);
		void parse_cmd(std::string str);
    
	private:
    	std::map<std::string, ptr_ft>	_cmd;
};

//parametre : ref sur la struct avec les donnees utiles a utiliser pour les cds (_value/args, )
void nick(Cmd::Command & command);
void user(Cmd::Command & command);
void quit(Cmd::Command & command);

void join(Cmd::Command & command);
void list(Cmd::Command & command);

void privmsg(Cmd::Command & command);
void who(Cmd::Command & command);

void invite(Cmd::Command & command);
void kick(Cmd::Command & command);
void oper(Cmd::Command & command);
void kill(Cmd::Command & command);
void whois(Cmd::Command & command);
void pass(Cmd::Command & command);
void names(Cmd::Command & command);

#endif