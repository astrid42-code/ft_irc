#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <locale>

namespace irc{

    class Server{
        public:
            Server();
            Server(int port, std::string pwd);
            Server(const Server &serv_op);
			~Server();

            Server  & operator=(const Server &serv_cp);

            std::string get_port() const;
            std::string get_pwd() const;
            bool set_pp(std::string port, std::string pwd); // parse et set le port et le pwd

            std::locale loc;
        
        private:
            std::string  _port;
            std::string  _pwd;
    };

}

#endif