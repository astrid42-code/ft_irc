#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <locale>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <map>
#include <netdb.h>
#include "../Channel/Channel.hpp"
#include "../Command/Cmd.hpp"


class User;
class Channel;
class Cmd;

class Server
{
	public:
		Server();
		Server(std::string port, std::string pwd);
		Server(const Server &serv_op);
		~Server();

		Server		&operator=(const Server &serv_cp);
		std::string	get_port() const;
		std::string	get_pwd() const;
		bool		set_pp(std::string port, std::string pwd); // parse et set le port et le pwd
		void		onCmdReceived(std::string cmd);
		void		onConnection(Channel chan);
		void		onMessageReceived(Channel chan, User usr);
		void		onDeconnection(Channel chan);
		int			init();
		Channel		get_chan(std::string key);
		bool		set_chan(Channel chan);
		User		get_user(std::string key);
		std::string	get_ip();
		void 		set_ip(std::string ip);
		bool		set_user(User user);
		std::locale	loc;
		std::string	get_msg(std::string msg, User *user, Cmd &cmd);
		// faire une fct qui recupere les msg et les imprime (stocke dans _msg)

	private:
		std::string							_port; // doit etre une string car recupere av[1] -> a transformer en int pour plus de simplicite	
		std::string							_pwd;
		int									fd;
		std::string 						_ip;
		std::string							_msg; // msg envoye par le serveur (ex : msgs d'erreurs)
		std::map< std::string, Channel>	_channels;
		std::map< std::string, User>		_users;
};


#endif