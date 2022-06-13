/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:44:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/06/13 18:12:51 by asgaulti         ###   ########.fr       */
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
	if (_port.size() != 4 || !std::isdigit(port, loc)){
		std::cout << "There is an error in arguments!" << std::endl;
		return (false);
	}
	_pwd = pwd;
	return (true);
}

}

// pbs :
// 1 si erreur, mets bien le msg (mais cree le serveur donc a faire plutot dans le constructeur??)
// 2 si pas d'erreur std::bad_cast