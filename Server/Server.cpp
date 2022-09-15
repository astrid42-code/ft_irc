/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:44:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/15 20:10:57 by asgaulti         ###   ########.fr       */
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

bool Server::set_pp(std::string port, std::string pwd)
{
	_port = port;
	_pwd = pwd;
	// if (_port.size() != 4){
	// 	std::cout << "There is an error in arguments!" << std::endl;
	// 	return (false);
	// }
	// for (int i = 0; i < 4; i++){
	// 	 if (!std::isdigit(_port[i], loc)){
	// 		std::cout << "There is an error in arguments!" << std::endl;
	// 		return (false);
	// 	}
	// }
	// verifier la taille du pwd? (verifier dans les regles si taille min/max)
	return (true);
}
/*
	void onCmdReceived(std::string cmd) // /connect 127.0.0.1 6667 // /join ChannelID // msg "ID" "salut" // "wdhqiwudhqwuidhqwudhqwiudhwquidhqwiuhdqwuihdqwhiudqwhuidhq"
	{
		// appeler les fonctions onConnection, onMessageReceived, onDeconnection ... en fonction
		// du retour du parsing
	}

	void onConnection(Channel chan, User usr)
	{
		//appeler la fonction chan.addUser(User usr) qui doit ajouter le User usr au Channel chan
	}

	void onMessageReceived(Channel chan, User usr, std::string msg)
	{
		// appeler la fonction chan.message(User usr, std::string msg) qui doit envoyer le message msg
		// a tout les User de chan sauf usr
	}

	void onDeconnection(Channel chan, User usr)
	{
		//appeler la fonction chan.delUser() qui doit remove le User usr du Channel chan
	}
*/

std::string Server::get_msg(std::string msg, User *user, Cmd &cmd)
{
	std::string	res = ":";
	std::string arg;

	if (msg.compare("RPL_WELCOME") == 0)
	{
		// res.append(cmd.get_value()[0]);
		// for (int i = 1; i < cmd.get_size() - 1; i++)
			// res.append(cmd.get_value()[i] + " "); // ex dasanter!dasanter@127.0.0.1
		arg.append(cmd._user->get_nick());
		arg.append("!");
		arg.append(cmd._user->get_user());
		arg.append("@");
		arg.append(" 001 ");
		arg.append(cmd._user->get_host());
		arg.append("\r\n");
		
		
		res.append(RPL_WELCOME(arg));
	}
	if (msg.compare("RPL_YOURHOST") == 0)
	{
		res.append(RPL_YOURHOST);
	}
	if (msg.compare("RPL_CREATED") == 0)
	{
		res.append(RPL_CREATED);
	}
	if (msg.compare("RPL_MYINFO") == 0)
	{
		res.append(RPL_MYINFO(user->get_mod(), "0"));
	}
	if (msg.compare("RPL_MOTD") == 0){
		res.append(RPL_MOTDSTART);
		arg = "\n\
dHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHb \n\
HHP%%#%%%%%%%%%%%%%%%%#%%%%%%%#%%VHH \n\
HH%%%%%%%%%%#%v~~~~~~\\%%%#%%%%%%%%HH \n\
HH%%%%%#%%%%v'        ~~~~\\%%%%%#%HH \n\
HH%%#%%%%%%v'dHHb      a%%%#%%%%%%HH \n\
HH%%%%%#%%v'dHHHA     :%%%%%%#%%%%HH \n\
HH%%%#%%%v' VHHHHaadHHb:%#%%%%%%%%HH \n\
HH%%%%%#v'   `VHHHHHHHHb:%%%%%#%%%HH \n\
HH%#%%%v'      `VHHHHHHH:%%%#%%#%%HH \n\
HH%%%%%'        dHHHHHHH:%%#%%%%%%HH \n\
HH%%#%%        dHHHHHHHH:%%%%%%#%%HH \n\
HH%%%%%       dHHHHHHHHH:%%#%%%%%%HH \n\
HH#%%%%       VHHHHHHHHH:%%%%%#%%%HH \n\
HH%%%%#   b    HHHHHHHHV:%%%#%%%%#HH \n\
HH%%%%%   Hb   HHHHHHHV'%%%%%%%%%%HH \n\
HH%%#%%   HH  dHHHHHHV'%%%#%%%%%%%HH \n\
HH%#%%%   VHbdHHHHHHV'#%%%%%%%%#%%HH \n\
HHb%%#%    VHHHHHHHV'%%%%%#%%#%%%%HH \n\
HHHHHHHb    VHHHHHHH:%odHHHHHHbo%dHH \n\
HHHHHHHHboodboooooodHHHHHHHHHHHHHHHH \n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH \n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH \n\
VHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHGGN94\r\n"; 
		res.append(RPL_MOTD(arg));
		res.append(RPL_ENDOFMOTD);
	}
		
	//:dasanter!dasanter@127.0.0.1 001 dasanter :Welcome to the Internet Relay Network
	//std::cout << "OUAI : " << res << std::endl;
	// effacer le contenu du vector _value
	// for (int i = 1; i < cmd.get_size(); i++)
	// 	cmd.get_value()[i].clear();

	// if (msg = les msgs 001 002 ou 003)
	// mettre les infos de demarrage du serveur en + du define du RPL_answer.hpp)
	std::cout << "get msg : |" << res << "|" << std::endl;
	send(cmd._sfd, res.c_str(), res.length(), MSG_CONFIRM);
	return (res);
}

static int make_socket_non_blocking(int sfd)
{
	int flags, s;
	flags = fcntl(sfd, F_GETFL, 0);
	if (flags == -1)
	{
		perror("fcntl");
		return -1;
	}
	flags |= O_NONBLOCK;
	s = fcntl(sfd, F_SETFL, flags);
	if (s == -1)
	{
		perror("fcntl");
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
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;
		s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
		if (s == 0)
		{
			/* We managed to bind successfully! */
			break;
		}
		close(sfd);
	}
	if (rp == NULL)
	{
		fprintf(stderr, "Could not bind\n");
		return -1;
	}
	freeaddrinfo(result);
	return (sfd);
}

void pre_parse(std::string buf, int sfd, Server *serv)
{
	int pos = 0;
	std::string token;

	std::cout << "buf = " << buf << std::endl;
	while (pos < (int)buf.length() && buf.find("\r\n", pos))
	{
		Cmd command;
		command._server = serv;
		command._sfd = sfd;
		token = buf.substr(pos, buf.find("\r\n", pos) - pos);
		pos = buf.find("\n", pos) + 1;
		std::cout << "token = |" << token << "|" << std::endl;
		command.parse_cmd(token);
		if (pos >= (int)buf.length() || pos == 0)
			break ;
	}
}

// https://www.ibm.com/docs/en/i/7.3?topic=designs-example-nonblocking-io-select
int Server::init()
{
	int sfd, s;
	int efd;
	struct epoll_event event;
	struct epoll_event *events;

	sfd = create_and_bind(_port.c_str());
	if (sfd == -1)
		abort();
	s = make_socket_non_blocking(sfd);
	if (s == -1)
		abort();
	s = listen(sfd, SOMAXCONN);
	if (s == -1)
	{
		perror("listen");
		abort();
	}
	efd = epoll_create1(0);
	if (efd == -1)
	{
		perror("epoll_create");
		abort();
	}
	event.data.fd = sfd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);
	if (s == -1)
	{
		perror("epoll_ctl");
		abort();
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
				fprintf(stderr, "epoll error\n");
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
							perror("accept");
							break;
						}
					}
					s = getnameinfo(&in_addr, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf, NI_NUMERICHOST | NI_NUMERICSERV);
					if (s == 0)
					{
						printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", infd, hbuf, sbuf);
						printf("after connect\n");
					}
					s = make_socket_non_blocking(infd);
					if (s == -1)
						abort();
					event.data.fd = infd;
					event.events = EPOLLIN | EPOLLET;
					s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
					if (s == -1)
					{
						perror("epoll_ctl");
						abort();
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
					count = read(events[i].data.fd, buf, sizeof buf);
					if (count == -1)
					{
						if (errno != EAGAIN)
						{
							perror("read");
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
					printf("Closed connection on descriptor %d\n", events[i].data.fd);
					close(events[i].data.fd);
				}
			}
		}
	}
	free(events);
	close(sfd);
	return (EXIT_SUCCESS);
}

// recuperer la data du User
Channel *Server::get_chan(std::string key)
{
	std::map<std::string, Channel>::iterator it;
	std::cout << "start" << std::endl;
	it = _channels.find(key);
	std::cout << "mid" << std::endl;
	if (it->second.get_name() == _channels.end()->second.get_name())
	{
		std::cout << "NULL" << std::endl;
		return (NULL);
	}
	std::cout << "end" << std::endl;
	return ((&it->second));
}

// insert user in map
bool Server::set_chan(Channel chan)
{
	std::pair<std::map<std::string, Channel>::iterator, bool> p;

	p = _channels.insert(make_pair(chan.get_name(), chan));
	return (p.second); // if bool == true user succesfully join server else nick name already in use
}

std::map< std::string, User> Server::get_users(void)
{
	return (_users);
}

// recuperer la data du User
User Server::get_user(std::string key)
{
	std::map<std::string, User>::iterator it;

	it = _users.find(key);
	if (it == _users.end())
		return (User());
	return (it->second);
}
// insert user in map
bool Server::set_user(User user)
{
	std::pair<std::map<std::string, User>::iterator, bool> p;

	p = _users.insert(make_pair(user.get_nick(), user));
	return (p.second); // if bool == true user succesfully join server else nick name already in use
}