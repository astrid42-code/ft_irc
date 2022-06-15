/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:44:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/06/15 18:20:03 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

namespace irc{
	
Server::Server() : _port("6667"), _pwd("pwd"){
	std::cout << "Hi there, nice to see you!" << std::endl;
}

// Server::Server(int port, std::string pwd) : _port(port), _pwd(pwd){
// 	// parser port et pwd ici ou dans une fct set plutot?
// 	// si tout ok, msg de bienvenue; sinon 
// }

Server::Server(const Server &serv_cp){
	*this = serv_cp;
}

Server::~Server(){
	// recuperer les Users (a mettre dans un vector, map pas utile ici car c pour tous les retirer)
	// > faire une fct get_users qui recupere tous les users
	// boucle for pour tous les delete (fct delUsers a creer)
	std::cout << "Bye, see you soon!" << std::endl;
}

Server  & Server::operator=(const Server &serv_op){
	_port = serv_op._port;
	_pwd = serv_op._pwd;
	return (*this);
}

std::string Server::get_port() const{
	return (_port);
}

std::string Server::get_pwd() const{
	return (_pwd);
}

bool	Server::set_pp(std::string port, std::string pwd){
	_port = port;
	if (_port.size() != 4){
		std::cout << "There is an error in arguments!" << std::endl;
		return (false);
	}
	for (int i = 0; i < 4; i++){
		 if (!std::isdigit(_port[i], loc)){
			std::cout << "There is an error in arguments!" << std::endl;
			return (false);
		}
	}
	_pwd = pwd;
	return (true);
}

// https://www.ibm.com/docs/en/i/7.3?topic=designs-example-nonblocking-io-select
int	Server::init(){
	int		i, len, rc, on = 1;
	int		listen_sd, max_sd, new_sd;
	int		desc_ready, end_server = false;
	int		close_conn;
	char	buffer[80];
	struct sockaddr_in6	addr;
	struct timeval		timeout;
	fd_set				master_set, working_set;

   /*************************************************************/
   /* Create an AF_INET6 stream socket to receive incoming      */
   /* connections on                                            */
   /*************************************************************/
   
   if ((listen_sd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
   {
      perror("socket() failed");
      exit(-1);
   }

   /*************************************************************/
   /* Allow socket descriptor to be reuseable                   */
   /*************************************************************/
   
   if ((rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on))) < 0)
   {
      perror("setsockopt() failed");
      close(listen_sd); // mettre une fct cpp a la place
      exit(-1);
   }

	/*************************************************************/
   /* Set socket to be nonblocking. All of the sockets for      */
   /* the incoming connections will also be nonblocking since   */
   /* they will inherit that state from the listening socket.   */
   /*************************************************************/
   
//    if ((rc = ioctl(listen_sd, FIONBIO, (char *)&on)) < 0)
//    {
//       perror("ioctl() failed");
//       close(listen_sd);
//       exit(-1);
//    }

   /*************************************************************/
   /* Bind the socket                                           */
   /*************************************************************/
//    memset(&addr, 0, sizeof(addr));
//    addr.sin6_family      = AF_INET6;
//    memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
//    addr.sin6_port        = htons(SERVER_PORT);
   
   if ((rc = bind(listen_sd,
             (struct sockaddr *)&addr, sizeof(addr))) < 0)
   {
      perror("bind() failed");
      close(listen_sd);
      exit(-1);
   }

}

// recuperer la data du User
// User & Server::get_user() const { // reference or ptr? 
	
// }

}

// pb :
// si erreur, mets bien le msg (mais cree le serveur donc a faire plutot avant la creation du server??)
