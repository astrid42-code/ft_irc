#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>

namespace irc{

    class Server{
        public:
            Server();
            Server(int port, std::string pwd);
            Server(const Server &serv_op);
			~Server();

            Server  & operator=(const Server &serv_cp);

            int get_port() const;
            std::string get_pwd() const;
            bool set_pp(int port, std::string pwd); // parse et set le port et le pwd

        
        private:
            const int    _port;
            std::string  _pwd;
    };

}

#endif