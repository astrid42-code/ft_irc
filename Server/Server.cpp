/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:44:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/26 10:20:45 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "../Command/Cmd.hpp"

//#include "../User/User.hpp"
/* #include "../Command/RPL_answer.hpp"
	a decommenter quand on aura fait le User.cpp
	*/
// :nickname!username@IP CodeMessage Nickname :Message Que Tu Veux Mettre
// #define RPL_WELCOME (":dasanter!dasanter@127.0.0.1 001 dasanter :Welcome to the Internet Relay Network\r\n") // 001
// + envoyer <nick>!<user>@<host>) en arguments
// + ajouter dessin?
// #define RPL_YOURHOST (":dasanter!dasanter@127.0.0.1 002 dasanter :Your host is 127.0.0.1, running version 1.69\r\n")	 // 002
// #define RPL_CREATED (":dasanter!dasanter@127.0.0.1 003 dasanter :This server was created Mon Aug 5 16:57:33 2022\r\n") // 003
// #define RPL_MYINFO (":dasanter!dasanter@127.0.0.1 004 dasanter :irc_dta 1.69 aio ovim\r\n")														 // 004


/* TODO
**
// FAIRE recv() au lieu de read()
**
*/

#define TRUE 1
#define PORT 6668
#define MAXEVENTS 64
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sys/epoll.h>
#include <fcntl.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <cstring>

Server::Server() : _port("6667"), _pwd("pwd")
{
	std::cout << "Hi there, nice to see you!" << std::endl;
	set_ip(_ip);
}

Server::Server(std::string port, std::string pwd) : _port(port), _pwd(pwd)
{
	std::cout << "Hi there, nice to see you!" << std::endl;
	// parser port et pwd ici ou dans une fct set plutot?
	// si tout ok, msg de bienvenue; sinon
}

Server::Server(const Server &serv_cp)
{
	*this = serv_cp;
}

Server::~Server()
{
	// recuperer les Users (a mettre dans un vector, map pas utile ici car c pour tous les retirer)
	// > faire une fct get_users qui recupere tous les users
	// boucle for pour tous les delete (fct delUsers a creer)
	std::cout << "Bye, see you soon!" << std::endl;
}

Server &Server::operator=(const Server &serv_op)
{
	(void)serv_op;
	// _port = sefilerv_op._port;
	// _pwd = serv_op._pwd;
	return (*this);
}

std::string Server::get_ip()
{
	return (_ip);
}

void Server::set_ip(std::string ip)
{
	int sock = socket(PF_INET, SOCK_DGRAM, 0);
	sockaddr_in loopback;

	if (sock == -1)
	{
		std::cerr << "Could not socket\n";
		return;
	}

	std::memset(&loopback, 0, sizeof(loopback));
	loopback.sin_family = AF_INET;
	loopback.sin_addr.s_addr = 1337; // can be any IP address
	loopback.sin_port = htons(9);		 // using debug port

	if (connect(sock, reinterpret_cast<sockaddr *>(&loopback), sizeof(loopback)) == -1)
	{
		close(sock);
		std::cerr << "Could not connect\n";
		return;
	}

	socklen_t addrlen = sizeof(loopback);
	if (getsockname(sock, reinterpret_cast<sockaddr *>(&loopback), &addrlen) == -1)
	{
		close(sock);
		std::cerr << "Could not getsockname\n";
		return;
	}

	close(sock);

	char buf[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET, &loopback.sin_addr, buf, INET_ADDRSTRLEN) == 0x0)
	{
		std::cerr << "Could not inet_ntop" << std::endl;
		return;
	}
	else
	{
		std::cout << "Local ip address: " << buf << std::endl;
		ip = buf;
		return;
	}
}

/*std::string Server::form_msg(int code, std::string msg, User usr){
	return (msg);
}
*/
std::string Server::get_port() const
{
	return (_port);
}

std::string Server::get_pwd() const
{
	return (_pwd);
}

std::string	Server::send_msg(int rpl, std::string msg, Cmd &cmd)
{
	std::string	res = ":";
	std::string num_rpl = SSTR(rpl);

	res.append(msg);
	
	std::cout << "send msg : |" << res << "|" << std::endl;
	send(cmd._sfd, res.c_str(), res.length(), MSG_CONFIRM);
	return (res);	
}


// std::string    Server::send_msg(int rpl, std::string msg, Cmd &cmd)
// {
// 	std::string	res = ":";
// 	std::string num_rpl = SSTR(rpl);
	
// 	if (rpl == 42)
// 	{
// 		// std::string nicks = cmd._user->get_nick();
// 		// // res.append(nicks + " ");
// 		// res.append("JOIN" + msg.substr(0, msg.size()) + " ");
// 		// res.append(" @" + nicks + " ");
// 		// remplir la string avec les nicks qui sont dans le channel
// 		// tq les users presents dans le channel (it != users.end())
// 		// while (cmd._server->get_chan(msg)->get_users())
// 		// {
// 		// 	// if () // si le mode user est oper
// 		// 		nicks.append("@");
// 		// 	nicks.append(); // ajouter le nickname
// 		// 	// incrementer (mais quoi puisque pas d'iterator la ??)
// 		// }
// // ajouter les 2 define (353 et 366) dans le msg : en envoyant les msgs ou en append?
// 		// cmd._server->send_msg(353, RPL_NAMREPLY(msg, nicks), cmd);
// 		// cmd._server->send_msg(366, RPL_ENDOFNAMES(msg), cmd);
		
		
// 		res.append(cmd._user->get_hostname());
// 		res.append(" " + SSTR(353) + " ");
// 		res.append(cmd._user->get_nick() + " ");
// 		res.append(RPL_NAMREPLY(msg.substr(1, msg.size())));
		
// 		res.append("::");
// 		res.append(cmd._user->get_hostname());
// 		res.append(" " + SSTR(366) + " ");
// 		res.append(cmd._user->get_nick() + " ");
// 		res.append( RPL_ENDOFNAMES(msg.substr(1, msg.size())));
		
// 		// if (cmd._server->get_chan(msg)->get_topic() == ""){
// 		// 	res.append(cmd._user->get_hostname());
// 		// 	res.append(" " + SSTR(331) + " ");
// 		// 	if (cmd._user->get_nick() == "")
// 		// 		res.append("*");
// 		// 	else
// 		// 		res.append(cmd._user->get_nick());
// 		// 	res.append(" ");
// 		// 	res.append(RPL_NOTOPIC(msg));
// 		// }
// 		// else
// 		// {
// 		// 	res.append(cmd._user->get_hostname());
// 		// 	res.append(" " + SSTR(332) + " ");
// 		// 	if (cmd._user->get_nick() == "")
// 		// 		res.append("*");
// 		// 	else
// 		// 		res.append(cmd._user->get_nick());
// 		// 	res.append(" ");
// 		// 	res.append(RPL_TOPIC(msg, cmd._server->get_chan(msg)->get_topic()));
// 		// }
// 	// + checker si topic ou non et ajouter le rpl correspondant en fonction 
// 	// puis envoyer le tout aux users du channel

// 	// a verifier : doit on tout envoyer ensemble ou peut on envoyer au fur et a mesure?

// 	// std::cout << "nick = " << cmd._user->get_nick() << std::endl;

// std::cout << "debug send msg : |" << res << "|" << std::endl;
// 		send(cmd._sfd, res.c_str(), res.length(), MSG_CONFIRM);
// 		return (res);
// 	}
// 	else
// 	{
// 		res.append(cmd._user->get_hostname());
// 		res.append(" ");
		
// 		if (rpl < 10 && rpl != 0){
// 			res.append("00" + num_rpl + " ");
// 		}
// 		else if (rpl != 0 && rpl != 42)
// 			res.append(num_rpl + " ");
// 		else if (rpl == 0)	
// 			res.append(" ");
// 		if (cmd._user->get_nick() == "")
// 			res.append("*");
// 		else
// 			res.append(cmd._user->get_nick());
// 		res.append(" ");
// 	}
// 	res.append(msg);
	
// 	std::cout << "send msg : |" << res << "|" << std::endl;
// 	send(cmd._sfd, res.c_str(), res.length(), MSG_CONFIRM);
// 	return (res);
// }

static int make_socket_non_blocking(int sfd)
{
	int flags, s;

	flags = fcntl(sfd, F_GETFL, 0);
	if (flags == -1)
	{
		std::cerr << "fcntl" << std::endl;
		return -1;
	}
	flags |= O_NONBLOCK;
	s = fcntl(sfd, F_SETFL, flags);
	if (s == -1)
	{
		std::cerr << "fcntl" << std::endl;
		return -1;
	}
	return 0;
}

static int create_and_bind(std::string port)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s, sfd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;		 /* Return IPv4 and IPv6 choices */
	hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
	hints.ai_flags = AI_PASSIVE;		 /* All interfaces */
	s = getaddrinfo(NULL, port.c_str(), &hints, &result);
	if (s != 0)
	{
		std::cerr << "Error getaddrinfo" << std::endl;
		return -1;
	}
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;
		s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
		if (s == 0) /* We managed to bind successfully! */
			break;
		close(sfd);
	}
	if (rp == NULL)
	{
		std::cerr << "Could not bind" << std::endl;
		return -1;
	}
	freeaddrinfo(result);
	return (sfd);
}

void pre_parse(std::string buf, int sfd, Server *serv)
{
	std::size_t pos = 0;
	std::string token;

	std::cout << "buf = " << buf << std::endl;
	User *usr = serv->get_user(sfd);
	usr->buf.append(buf);
	while (pos < usr->buf.length() && usr->buf.find("\r\n", pos) != std::string::npos)
	{
		// std::cout << "Command " << std::endl;
		Cmd *command = new Cmd();
		// std::cout << "serv " << std::endl;
		command->_server = serv;
		// std::cout << "sfd " << std::endl;
		command->_sfd = sfd;
		// std::cout << "get_user_fd " << std::endl;
		command->_user = command->get_user_fd();
		if (command->_user == NULL)
		{
			std::cout << "_____NoUserFromFd_____" << std::endl;
		}
		else
		{
			std::cout << "_____UserFromFd_____" << std::endl;
			command->_user->print();
		}
		if ((usr->buf.find("\r\n", pos)) != std::string::npos)
		{
			token = usr->buf.substr(pos, usr->buf.find("\r\n", pos) - pos);
			usr->buf = usr->buf.substr(usr->buf.find("\r\n", pos) + 2);
		}
		else
			pos = usr->buf.length();
		std::cout << "token :|" << token << "|" << std::endl;
		command->parse_cmd(token);
		delete command;
	}
}	

// https://www.ibm.com/docs/en/i/7.3?topic=designs-example-nonblocking-io-select
int	Server::init()
{
	int sfd, s;
	int efd;
	struct epoll_event event;
	struct epoll_event *events;

	sfd = create_and_bind(_port.c_str());
	if (sfd == -1)
		exit(1);
	s = make_socket_non_blocking(sfd);
	if (s == -1)
		return (-1);
	s = listen(sfd, SOMAXCONN);
	if (s == -1)
	{
		std::cerr << "listen" << std::endl;
		return (-1);

	}
	efd = epoll_create1(0);
	if (efd == -1)
	{
		std::cerr << "epoll_create" << std::endl;
		return (-1);
	}
	event.data.fd = sfd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);
	if (s == -1)
	{
		std::cerr << "epoll_ctl" << std::endl;
		return (-1);
	}
	/* Buffer where events are returned */
	events = (epoll_event *)calloc(MAXEVENTS, sizeof(event));
	/* The event loop */
	while (1)
	{
		int n, i;
		n = epoll_wait(efd, events, MAXEVENTS, -1);
		for (i = 0; i < n; i++)
		{
			if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
			{
				/* An error has occured on this fd, or the socket is not
					 ready for reading (why were we notified then?) */
				std::cerr << "epoll error" << std::endl;
				close(events[i].data.fd);
				continue;
			}
			else if (sfd == events[i].data.fd)
			{
				/* We have a notification on the listening socket, which
					 means one or more incoming connections. */
				while (1)
				{
					struct sockaddr in_addr;
					socklen_t in_len;
					int infd;
					char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

					in_len = sizeof in_addr;
					infd = accept(sfd, &in_addr, &in_len);
					if (infd == -1)
					{
						if ((errno == EAGAIN) ||
								(errno == EWOULDBLOCK))
						{
							break;
						}
						else
						{
							std::cerr << "accept" << std::endl;
							break;
						}
					}
					s = getnameinfo(&in_addr, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf, NI_NUMERICHOST | NI_NUMERICSERV);
					if (s == 0)
					{
						this->set_user(new User(infd));
						std::cout << "Accepted connection on descriptor " << infd << "(host=" << hbuf << ", port=" << sbuf << ")" << std::endl;
					}
					s = make_socket_non_blocking(infd);
					if (s == -1)
						return (-1);
					event.data.fd = infd;
					event.events = EPOLLIN | EPOLLET;
					s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
					if (s == -1)
					{
						std::cerr << "epoll_ctl" << std::endl;
						return (-1);
					}
				}
				continue;
			}
			else
			{
				int done = 0;
				while (1)
				{
					ssize_t count;
					char buf[512];
					bzero(buf, 512);
					count = recv(events[i].data.fd, buf, sizeof(buf), MSG_DONTWAIT);
					if (count == -1)
					{
						if (errno != EAGAIN)
						{
							std::cerr << "read" << std::endl;
							done = 1;
						}
						break;
					}
					else if (count == 0)
					{
						done = 1;
						break;
					}
					pre_parse(buf, events[i].data.fd, this);
				}
				if (done)
				{
					std::cout << "Closed connection on descriptor " << events[i].data.fd << std::endl;
					close(events[i].data.fd);
				}
			}
		}
	}
	
	free(events);
	close(sfd);
	return (EXIT_SUCCESS);
}

void	Server::remove_user(User *user)
{
	std::vector<Channel *> v_chan;
	std::vector<Channel *>::iterator it;


	v_chan = user->get_chans();
	it = v_chan.begin();
	while (it != v_chan.end())
	{
		(*it)->remove_user(user);
		it++;
	}
	_users.erase(_users.find(user->get_sfd()));
}


// recuperer la data du User
Channel	*Server::get_chan(std::string key)
{
	std::map<std::string, Channel *>::iterator it;
	// for (it = _channels.begin(); it != _channels.end(); it++){
	// 	std::cout << "it name " << it->second->get_name() << std::endl;
	// }
	std::cout << "start" << std::endl;

	// std::cout << "tmp_key = " << tmp_key << std::endl;
	it = _channels.find(key);
	// std::cout << "mid" << std::endl;
	if (it == _channels.end())
	{
		std::cout << "NULL" << std::endl;
		return (NULL);
	}
	// std::cout <<  << it->second->size() << std::endl;
	std::cout << "end" << std::endl;
	return (it->second);
}

// size_t	Server::get_chan_size()

// insert user in map
bool	Server::set_chan(Channel *chan)
{
	std::pair<std::map<std::string, Channel *>::iterator, bool> p;

	p = _channels.insert(make_pair(chan->get_name(), chan));
	std::cout << "channel name " << chan->get_name() << std::endl;	
	// chan->set_name(chan->get_name());
	return (p.second); // if bool == true user succesfully join server else nick name already in use
}
// set le channel dans le serveur (la fct set_channel de Channel est inutilisee donc)


std::map<int, User *>	Server::get_users(void) const
{
	return (_users);
}

std::map<std::string, Channel *>	Server::get_chans(void) const
{
	return (_channels);
}

// recuperer la data du User
User	*Server::get_user(int key)
{
	std::map<int, User *>::iterator it;

	it = _users.find(key);
	if (it == _users.end())
		return (NULL);
	return (it->second);
}

User	*Server::get_user(std::string nick)
{
	std::cout << "OUAI" << std::endl;
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		std::cout << "get_user boucle" << std::endl;
		if (it->second->get_nick() == nick)
			return (it->second);
	}
	return (NULL);
}


// insert user in map
bool	Server::set_user(User *user)
{
	std::pair<std::map<int, User *>::iterator, bool> p;

	std::cout << "set_user server " << user->get_sfd() << std::endl;
	p = _users.insert(std::make_pair(user->get_sfd(), user));
	return (p.second); // if bool == true user succesfully join server else nick name already in use
}

void	Server::set_user_in_chan(User *user, Channel *chan)
{
	std::vector<Channel *>::iterator it;
	
	chan->set_user(user);
	user->set_chan(*chan);
	// std::cout << "coucou2 user = " << chan->get_user(user->get_sfd()) << std::endl;
	// for (it = user->_vchan.begin(); it != user->_vchan.end(); it++)
	// for (int i = 0; i < user->get_chan.size(); i++)
	// {
	// 	std::cout << "chan user : " << user->get_chan(i) << std::endl;
	// }
}

