#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include "../User/User.hpp"
#include "../Server/Server.hpp"
#include "../RPL_answer.hpp"

class User;

class Server;

class Cmd
{

	public:
		Cmd();
		Cmd(const Cmd & cp);
		~Cmd();

		Server					*_server;
		User					*_user; // recuperer les infos d'un user (nick, pwd, ...) 
		int 					_sfd;
		Cmd & operator=(const Cmd &cmd_op);

		// ptr sur fonction des cmds qui prend une ref sur ma struct Command
		typedef void (*ptr_ft)(Cmd &command);
		std::map<std::string, ptr_ft>::iterator	it;

		void							set_key(std::string key);
		const std::string				get_key(void) const;
		void							set_value(std::vector<std::string> key);
		std::vector<std::string>		get_value(void) const;
		void							set_size(int i);
		int								get_size(void) const;
		User							*get_user_fd();
		// void set_value(std::string value);
		// const std::string &	get_value(void) const;

		void	parse_cmd(std::string str);
		void	print(void);

		
	private:
		std::map<std::string, ptr_ft>	_cmd; // map avec ptr sur fct pour lancer les cmds
		std::string						_key; // la string du 1er element recu (la key de ma map)
		std::vector<std::string>		_value; // les args apres la commande (en vector pour en recevoir plsrs si necessaire)
		int								_size; // taille du vector value (il ne faut pas utiliser ca... mais _cmd.size())
};

//parametre : ref sur la struct avec les donnees utiles a utiliser pour les cds (_value/args, )
void	nick(Cmd &command);
void	user(Cmd &command);
void	quit(Cmd &command);
void	join(Cmd &command);
void	part(Cmd &command);
void	part(Cmd &command);
void	list(Cmd &command);

void	privmsg(Cmd &command);
void	who(Cmd &command);

void	ping(Cmd &command);
void	pong(Cmd &command);
void	invite(Cmd &command);
void	kick(Cmd &command);
void	oper(Cmd &command);
void	kill(Cmd &command);
void	whois(Cmd &command);
void	pass(Cmd &command);
void	names(Cmd &command);
void	mode(Cmd &command);

#endif