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
namespace irc{

    class User;
    class Channel;

    class Server{
        public:
            Server();
            Server(std::string port, std::string pwd);
            Server(const Server &serv_op);
			~Server();

            Server  & operator=(const Server &serv_cp);

            std::string get_port() const;
            std::string get_pwd() const;
            bool set_pp(std::string port, std::string pwd); // parse et set le port et le pwd
            void onCmdReceived(std::string cmd);
            void onConnection(Channel chan);
            void onMessageReceived(Channel chan, User usr);
            void onDeconnection(Channel chan);
            int	init();
            User & get_user() const;
            std::locale loc;
        
        private:
            std::string		_port; // doit etre une string car recupere av[1] -> a transformer en int pour plus de simplicite	
            std::string		_pwd;
            int fd;
            //std::map< std::string, Channel > _channels;
            //std::map< int, User *>	_users;
    };
}

#endif