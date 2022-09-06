/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:44:24 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/06 11:29:23 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#define TRUE   1
#define PORT 6667
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <unistd.h>
#include <algorithm>
#include <sys/types.h>
#include <netdb.h>
namespace irc{
	
Server::Server() : _port("6667"), _pwd("pwd"){
	std::cout << "Hi there, nice to see you!" << std::endl;
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

void Server::get_msg(std::string msg){
	(void)msg;
	// pour chaque msg : cela commence systematiquement par l'heure actuelle
	// (fct strtime() a utiliser?)
	
	// if (msg = les msgs 001 002 ou 003)
	// mettre les infos de demarrage du serveur en + du define du RPL_answer.hpp)

	// else
	
}


// https://www.ibm.com/docs/en/i/7.3?topic=designs-example-nonblocking-io-select
int	Server::init(){
    int is_ok = 1;
	int ret;
    struct sockaddr_in address;
	char buf[513];
	int cfd;
	std::ifstream	test;
	std::string RPL_WELCOME = "Welcome to the Internet Relay Network dasanter!dasanter@127.0.0.1\r\n";


	
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
		std::cout << "fail socket" << std::endl;
        return 0;
    }
	std::cout << fd << std::endl;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &is_ok, sizeof(is_ok)))
    {
		std::cout << "fail setsockopt" << std::endl;
        return 0;
    }
    // if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
    // {
    //         return 0;
    // }
    address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	struct addrinfo *res = NULL;
	getaddrinfo("127.0.0.1", "6667", (const struct addrinfo*)&address, &res);
    if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
		std::cout << "fail bind" << std::endl;
        return 0;
    }
    if (listen(fd, address.sin_port) < 0)
    {
		std::cout << "fail listen" << std::endl;
        return 0;
    }
    while (1)
    {
		cfd = accept(fd, (struct sockaddr *)NULL, NULL);

        ret = recv(cfd, buf, 513, 0);
		if (ret > 0)
		{
			buf[ret] = 0;
			printf("%s\n", buf);
		}
		printf("%d\n", ret);
		send(cfd ,RPL_WELCOME.c_str(), RPL_WELCOME.length(), MSG_NOSIGNAL);
    }
//     int master_sock , addrlen , new_sock , client_sock[30] ,
//             maximum_clients = 30 , act, i , value_read , sock_descriptor;
//     int maximum_socket_descriptor;
//     struct sockaddr_in adr;

//     char buff[1025];  //data buffer of 1K
//     fd_set readfds; //set of socket file descriptors
    
//     for (i = 0; i < maximum_clients; i++) //initialise all client_sock to 0 
//     {
//         client_sock[i] = 0;
//     }

//     if( (master_sock = socket(AF_INET , SOCK_STREAM , 0)) == 0) //creating a master socket 
//     {
//         perror("Failed_Socket");
//         exit(EXIT_FAILURE);
//     }

//     //These are the types of sockets that we have created
//     adr.sin_family = AF_INET;
//     adr.sin_addr.s_addr = INADDR_ANY;
//     adr.sin_port = htons( PORT );
    
//     if (bind(master_sock, (struct sockaddr *)&adr, sizeof(adr))<0) //bind the socket to localhost port 5500
//     {
//         perror("Failed_Bind");
//         exit(EXIT_FAILURE);
//     }
//     printf("Port having listener:  %d \\n", PORT);
    
//     if (listen(master_sock, 3) < 0) //Specify 3 as maximum pending connections for master socket
//     {
//         perror("listen");
//         exit(EXIT_FAILURE);
//     }
    
//     addrlen = sizeof(adr); //Accepting the Incoming Connection 
//     puts("Looking For Connections");
    
//     //*******************************//
//     // Here we start using select functions and the macros for multiple client handling
    
//     while(TRUE)
//     {
//         FD_ZERO(&readfds); //Clearing the socket set
//         FD_SET(master_sock, &readfds); //Adding the master socket to the set 
//         maximum_socket_descriptor = master_sock;
        
//         for ( i = 0 ; i < maximum_clients ; i++) //Adding child sockets to set 
//         {
//             sock_descriptor = client_sock[i]; //Descriptor for Socket 
            
//             if(sock_descriptor > 0) //if the socket descriptor is valid then adding it to the read list 
//                 FD_SET( sock_descriptor , &readfds);

//             if(sock_descriptor > maximum_socket_descriptor) //Highest File Descriptor Number which is needed for the select function 
//                 maximum_socket_descriptor = sock_descriptor;
//         }

//         //Waiting for something to happen on the master socket. As the wait time is NULL the wait is indefinite
//         act = select( maximum_socket_descriptor + 1 , &readfds , NULL , NULL , NULL);

//         if ((act < 0) && (errno!=EINTR))
//         {
//             printf("Failed_Select");
//         }
//         if (FD_ISSET(master_sock, &readfds)) //Any activity on the master socket is treated as an incoming connection
//         {
//             if ((new_sock = accept(master_sock,
//                                      (struct sockaddr *)&adr, (socklen_t*)&addrlen))<0)
//             {
//                 perror("Accept!");
//                 exit(EXIT_FAILURE);
//             }

//             //Informing the user of the socket number which will be sued to send and receive messages
//           /*  printf("This is a New Connection,The socket file descriptor is %d and the IP is : %s on Port : %d\\n"
//                    , new_sock , inet_ntoa(adr.sin_addr) , ntohs
//                     (adr.sin_port));
//             *///puts("Welcome Text Sent Affirmative.");

//             for (i = 0; i < maximum_clients; i++) // Adding new socket to the array of sockets
//             {
//                 if( client_sock[i] == 0 ) // Checking if the position is empty
//                 {
//                     client_sock[i] = new_sock;
//                     break;
//                 }
//             }
//         }
//         for (i = 0; i < maximum_clients; i++) //If not the master socket then it is some i/o activity on some other socket
//         {
//             sock_descriptor = client_sock[i];
//             if (FD_ISSET( sock_descriptor , &readfds))
//             {
//                 //Checking if the activity was for closing and reading the incoming message
//                 if ((value_read = read( sock_descriptor , buff, 1024)) == 0)
//                 {
//                     //If someone disconnected, getting their details and printing a message
//                     getpeername(sock_descriptor , (struct sockaddr*)&adr ,  (socklen_t*)&addrlen);
//                     printf("Disconnected Host. Their , IP %s and PORT %d \\n" ,
//                            inet_ntoa(adr.sin_addr) , ntohs(adr.sin_port));
//                     close( sock_descriptor ); //Closing the socket and marking it as 0 in the list to be reused
//                     client_sock[i] = 0;
//                 }
//                 else //Echoing back the message that came in the socket
//                 {
//                     buff[value_read] = 0; //Setting the string terminating NULL byte on the end of the data that is read
//                     send(sock_descriptor , buff , strlen(buff) , 0 );
//                 }
//             }
//         }
//     }
//     return 0;
// // 	int		i, len, rc, on = 1;
// // 	int		listen_sd, max_sd, new_sd;
// // 	int		desc_ready, end_server = false;
// // 	int		close_conn;	
// // 	char	buffer[80];
// // 	struct sockaddr_in6	addr;
// // 	struct timeval		timeout;
// // 	fd_set				master_set, working_set;

// //    /*************************************************************/
// //    /* Create an AF_INET6 stream socket to receive incoming      */
// //    /* connections on                                            */
// //    /*************************************************************/
   
// //    if ((listen_sd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
// //    {
// //       perror("socket() failed");
// //       exit(-1);
// //    }

// //    /*************************************************************/
// //    /* Allow socket descriptor to be reuseable                   */
// //    /*************************************************************/
   
// //    if ((rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR,
// //                    (char *)&on, sizeof(on))) < 0)
// //    {
// //       perror("setsockopt() failed");
// //       close(listen_sd); // mettre une fct cpp a la place
// //       exit(-1);
// //    }

// // 	/*************************************************************/
// //    /* Set socket to be nonblocking. All of the sockets for      */
// //    /* the incoming connections will also be nonblocking since   */
// //    /* they will inherit that state from the listening socket.   */
// //    /*************************************************************/
   
// // //    if ((rc = ioctl(listen_sd, FIONBIO, (char *)&on)) < 0)
// // //    {
// // //       perror("ioctl() failed");
// // //       close(listen_sd);
// // //       exit(-1);
// // //    }

// //    /*************************************************************/
// //    /* Bind the socket                                           */
// //    /*************************************************************/
// // //    memset(&addr, 0, sizeof(addr));
// // //    addr.sin6_family      = AF_INET6;
// // //    memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
// // //    addr.sin6_port        = htons(SERVER_PORT);
   
// //    if ((rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr))) < 0)
// //    {
// //       perror("bind() failed");
// //       close(listen_sd);
// //       exit(-1);
// //    }
 	return (0);
}

// recuperer la data du User
// User & Server::get_user() const { // reference or ptr? 
	
// }

}
