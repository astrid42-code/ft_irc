/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:44:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:32:39 by asgaulti         ###   ########.fr       */
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

Server::Server() : _port("6667"), _pwd("pwd"), _time(std::time(NULL))
{
	std::cout << "Hi there, nice to see you!" << std::endl;
	set_ip(_ip);
	srv_events = NULL;
	_users = new std::map<int, User *>();
	_channels = new std::map<std::string, Channel *>();
}

Server::Server(std::string port, std::string pwd) : _port(port), _pwd(pwd), _time(std::time(NULL))
{
	std::cout << "Hi there, nice to see you!" << std::endl;
	_users = new std::map<int, User *>();
	_channels = new std::map<std::string, Channel *>();
	srv_events = NULL;
}

Server::Server(const Server &serv_cp)
{
	*this = serv_cp;
}

Server::~Server()
{
	std::cout << "Bye, see you soon!" << std::endl;
	delete _users;
	delete _channels;
	if (srv_events != NULL)
		free(srv_events);
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

std::string Server::get_port() const
{
	return (_port);
}

std::string Server::get_pwd() const
{
	return (_pwd);
}


std::map<int, User *>	*Server::get_users(void) const
{
	return (_users);
}

std::map<std::string, Channel *>	*Server::get_chans(void) const
{
	return (_channels);
}

User	*Server::get_user(int key)
{
	std::map<int, User *>::iterator it;

	it = _users->find(key);
	if (it == _users->end())
		return (NULL);
	return (it->second);
}

User	*Server::get_user(std::string nick)
{
	for (std::map<int, User *>::iterator it = _users->begin(); it != _users->end(); it++)
	{
		if (it->second->get_nick().compare(nick) == 0)
			return (it->second);
	}
	return (NULL);
}

Channel	*Server::get_chan(std::string key)
{
	std::map<std::string, Channel *>::iterator it;

	it = _channels->find(key);
	if (it == _channels->end())
		return (NULL);
	return (it->second);
}

std::time_t	Server::get_time()
{
	return(_time);
}

void	Server::set_time(std::time_t time)
{
	_time = time;
}

void	Server::set_pwd(std::string pwd)
{
	_pwd = pwd;
}

bool	Server::set_chan(Channel *chan)
{
	std::pair<std::map<std::string, Channel *>::iterator, bool> p;

	p = _channels->insert(make_pair(chan->get_name(), chan));
	return (p.second); // if bool == true user succesfully join server else nick name already in use
}

// insert user in map
bool	Server::set_user(User *user)
{
	std::pair<std::map<int, User *>::iterator, bool> p;

	p = _users->insert(std::make_pair(user->get_sfd(), user));
	return (p.second); // if bool == true user succesfully join server else nick name already in use
}

void	Server::set_user_in_chan(User *user, Channel *chan)
{
	std::vector<Channel *>::iterator it;
	
	chan->set_user(user);
	user->set_chan(chan);
}

int	Server::send_msg(std::string msg, int sfd)
{
	int res;
	res = send(sfd, msg.c_str(), msg.length(), MSG_CONFIRM);
	return (res);
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
		ip = buf;
		return;
	}
}

static int make_socket_non_blocking(int sfd)
{
	int s;
	
	s = fcntl(sfd, F_SETFL, O_NONBLOCK);
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
		freeaddrinfo(result);
		freeaddrinfo(rp);
		return -1;
	}
	freeaddrinfo(result);
	return (sfd);
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
		return (-1);
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
	srv_events = events;
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
					char buf[3000];
					bzero(buf, 3000);
					count = recv(events[i].data.fd, buf, sizeof(buf), MSG_DONTWAIT);
					if (count == -1)
					{
						if (errno != EAGAIN)
						{
							std::cerr << "read" << std::endl;
							done = -1;
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
	_users->erase(_users->find(user->get_sfd()));
}
