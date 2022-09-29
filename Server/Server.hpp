#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
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

		Server					&operator=(const Server &serv_cp);

		std::string							get_port() const;
		std::string							get_pwd() const;
		void								set_pwd(std::string pwd);
		void								onCmdReceived(std::string cmd);
		void								onConnection(Channel chan);
		void								onMessageReceived(Channel chan, User usr);
		void								onDeconnection(Channel chan);
		int									init();
		Channel								*get_chan(std::string key);
		std::map<std::string, Channel *>	*get_chans() const;
		bool								set_chan(Channel *chan);
		User								*get_user(int key);
		User								*get_user(std::string nick);
		std::map<int, User *>				*get_users(void) const;
		std::string							get_ip();
		std::time_t							get_time();
		void								set_time(std::time_t time);
		void 								set_ip(std::string ip);
		bool								set_user(User *user);
		void								remove_user(User *user);
		
		std::locale							loc;

		// faire une fct qui recupere les msg et les imprime (stocke dans _msg)
		// std::string				get_msg(std::string msg, User	 *user, Cmd &cmd);
		int   								send_msg(std::string msg, int sfd);
		void								set_user_in_chan(User *user, Channel *chan);

	private:
		std::string							_port; // doit etre une string car recupere av[1] -> a transformer en int pour plus de simplicite	
		std::string							_pwd;
		int									fd;
		std::string 						_ip;
		std::string							_msg; // msg envoye par le serveur (ex : msgs d'erreurs)
		std::map<std::string, Channel *>	*_channels;
		std::map<int, User *>				*_users;
		std::time_t							_time;
};

//utils.cpp
std::vector<std::string>	div_string(std::string str, char c);
bool						mask_off(std::string mask, std::string str);
bool						erase_chan(Channel *chan, User *user);
void						pre_parse(std::string buf, int sfd, Server *serv);

#endif