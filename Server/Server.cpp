/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:44:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/06 16:47:47 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
//#include "../User/User.hpp"
/* #include "../Command/RPL_answer.hpp"
	a decommenter quand on aura fait le User.cpp
	*/
// :nickname!username@IP CodeMessage Nickname :Message Que Tu Veux Mettre
#define RPL_WELCOME (":dasanter!dasanter@127.0.0.1 001 dasanter :Welcome to the Internet Relay Network\r\n") //001
        	// + envoyer <nick>!<user>@<host>) en arguments 
			// + ajouter dessin?
#define RPL_YOURHOST ( ":dasanter!dasanter@127.0.0.1 002 dasanter :Your host is 127.0.0.1, running version 1.69\r\n") //002
#define RPL_CREATED (":dasanter!dasanter@127.0.0.1 003 dasanter :This server was created Mon Aug 5 16:57:33 2022\r\n") // 003
#define RPL_MYINFO (":dasanter!dasanter@127.0.0.1 004 dasanter :irc_dta 1.69 aio ovim\r\n") // 004
#define TRUE   1
#define PORT 6667
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
Server::Server() : _port("6667"), _pwd("pwd"){
	std::cout << "Hi there, nice to see you!" << std::endl;
	set_ip(_ip);
}

Server::Server(std::string port, std::string pwd) : _port(port), _pwd(pwd){
	// parser port et pwd ici ou dans une fct set plutot?
	// si tout ok, msg de bienvenue; sinon 
}

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

    if (sock == -1) {
        std::cerr << "Could not socket\n";
        return;
    }

    std::memset(&loopback, 0, sizeof(loopback));
    loopback.sin_family = AF_INET;
    loopback.sin_addr.s_addr = 1337;   // can be any IP address
    loopback.sin_port = htons(9);      // using debug port

    if (connect(sock, reinterpret_cast<sockaddr*>(&loopback), sizeof(loopback)) == -1) {
        close(sock);
        std::cerr << "Could not connect\n";
        return;
    }

    socklen_t addrlen = sizeof(loopback);
    if (getsockname(sock, reinterpret_cast<sockaddr*>(&loopback), &addrlen) == -1) {
        close(sock);
        std::cerr << "Could not getsockname\n";
        return;
    }

    close(sock);

    char buf[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &loopback.sin_addr, buf, INET_ADDRSTRLEN) == 0x0) {
        std::cerr << "Could not inet_ntop\n";
        return;
    } else {
        std::cout << "Local ip address: " << buf << "\n";
		ip = buf;
		return;
	}
}

/*std::string Server::form_msg(int code, std::string msg, User usr){
	return (msg);
}
*/
std::string Server::get_port() const{
	return (_port);
}

std::string Server::get_pwd() const{
	return (_pwd);
}

bool	Server::set_pp(std::string port, std::string pwd){
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

void Server::get_msg(std::string msg)
{
	(void)msg;
	// pour chaque msg : cela commence systematiquement par l'heure actuelle
	// (fct strtime() a utiliser?)
	
	// if (msg = les msgs 001 002 ou 003)
	// mettre les infos de demarrage du serveur en + du define du RPL_answer.hpp)

	// else
	
}

static int make_socket_non_blocking (int sfd)
{
  int flags, s;
  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      perror ("fcntl");
      return -1;
    }
  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      perror ("fcntl");
      return -1;
    }
  return 0;
}

static int create_and_bind (std::string port)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int s, sfd;
  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
  hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
  hints.ai_flags = AI_PASSIVE;     /* All interfaces */
  s = getaddrinfo(NULL, port.c_str(), &hints, &result);
  if (s != 0)
    {
      fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
      return -1;
    }
  for (rp = result; rp != NULL; rp = rp->ai_next)
    {
      sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
      if (sfd == -1)
        continue;
      s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
      if (s == 0)
        {
          /* We managed to bind successfully! */
          break;
        }
      close (sfd);
    }
  if (rp == NULL)
    {
      fprintf (stderr, "Could not bind\n");
      return -1;
    }
  freeaddrinfo (result);
  return sfd;
}

void  connect(int fd)
{
  	send(fd ,RPL_WELCOME, strlen(RPL_WELCOME), MSG_CONFIRM);
	send(fd ,RPL_YOURHOST, strlen(RPL_YOURHOST), MSG_CONFIRM); // 002
	send(fd ,RPL_CREATED, strlen(RPL_CREATED), MSG_CONFIRM); // 003
	send(fd ,RPL_MYINFO, strlen(RPL_MYINFO), MSG_CONFIRM); // 004
	send(fd ,"376 :End of MOTD command\r\n", strlen(":End of MOTD command\r\n"), MSG_CONFIRM); // 004
}

// https://www.ibm.com/docs/en/i/7.3?topic=designs-example-nonblocking-io-select
int	Server::init()
{
  int sfd, s;
  int efd;
  struct epoll_event event;
  struct epoll_event * events;
  sfd = create_and_bind("6667");
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
  s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, & event);
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
      if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN))) {
        /* An error has occured on this fd, or the socket is not
           ready for reading (why were we notified then?) */
        fprintf(stderr, "epoll error\n");
        close(events[i].data.fd);
        continue;
      } else if (sfd == events[i].data.fd) {
        /* We have a notification on the listening socket, which
           means one or more incoming connections. */
        while (1) {
          struct sockaddr in_addr;
          socklen_t in_len;
          int infd;
          char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

          in_len = sizeof in_addr;
          infd = accept(sfd, & in_addr, & in_len);
          if (infd == -1) {
            if ((errno == EAGAIN) ||
              (errno == EWOULDBLOCK)) {
              break;
            } else {
              perror("accept");
              break;
            }
          }
          s = getnameinfo( & in_addr, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf, NI_NUMERICHOST | NI_NUMERICSERV);
          if (s == 0) {
            connect(infd);
            printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", infd, hbuf, sbuf);
          }
          s = make_socket_non_blocking(infd);
          if (s == -1)
            abort();

          event.data.fd = infd;
          event.events = EPOLLIN | EPOLLET;
          s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, & event);
          if (s == -1) {
            perror("epoll_ctl");
            abort();
          }
        }
        continue;
      } else {
        int done = 0;
        while (1) {
          ssize_t count;
          char buf[512];
          count = read(events[i].data.fd, buf, sizeof buf);
          if (count == -1) {
            if (errno != EAGAIN) {
              perror("read");
              done = 1;
            }
            break;
          } else if (count == 0) {
            done = 1;
            break;
          }
          s = write(1, buf, count);
          if (s == -1) {
            perror("write");
            abort();
          }
        }
        if (done) {
          printf("Closed connection on descriptor %d\n",
            events[i].data.fd);
          close(events[i].data.fd);
        }
      }
    }
  }
  free(events);
  close(sfd);
  return EXIT_SUCCESS;
}

// recuperer la data du User
User *Server::get_user(int key)
{ // reference or ptr? 
	User	*user = NULL;
	std::map< int, User *>::iterator it = this->_users.begin();
	
	while (it != this->_users.end())
	{
		std::cout << it->first << " => " << it->second << std::endl;
		if (key == it->first)
			user = it->second;
		it++;
	}
	return (user); // if user == NULL no user for key
}
