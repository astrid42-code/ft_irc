/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:44:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/06/13 17:42:29 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

namespace irc{
	
Server::Server() : _port(6667), _pwd("pwd"){
	std::cout << "Hi there, nice to see you!" << std::endl;
}

// Server::Server(int port, std::string pwd) : _port(port), _pwd(pwd){
// 	// parser port et pwd ici ou dans une fct set plutot?
// 	// si tout ok, msg de bienvenue; sinon 
// }

Server::Server(const Server &serv_op){
	
}

Server::~Server(){
	std::cout << "Bye, see you soon!" << std::endl;
}

Server  & Server::operator=(const Server &serv_cp){
	return (*this);
}

int Server::get_port() const{
	return (_port);
}

std::string Server::get_pwd() const{
	return (_pwd);
}

bool	Server::set_pp(int port, std::string pwd){
	_port = get_port();
	_pwd = get_pwd();
}

}
