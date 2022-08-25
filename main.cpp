/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:31 by asgaulti          #+#    #+#             */
/*   Updated: 2022/08/25 16:55:01 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"
#include "Command/Cmd.hpp"

int main(int ac, char **av){

	(void)av;
	
	if (ac != 3){
		std::cout << "There is an error in arguments : ./ircserv <port> <password>" << std::endl;
		return (1);
	}
    
	// 1 creer un objet de la class irc::Server server > définir ce que l'objet server contient
	// > un objet config dans lequel on récupère port et pwd (en vérifiant qu'ils suivent les règles de taille d'irc?)
	// + récupérer le user (prévoir qu'il peut y en avoir plsrs, les mettre dans un tableau / vector)
	// + pvr delete les users
	// + de même avec les channels

	// irc::Server server = irc::Server();
	// server.init();
	
	Cmd	cmd = Cmd();
	cmd.exec_cmd("TEST");

	
	// test();
	// 2 signal?
	// 3 set le port et le pwd du server avec av1 et 2 (des possibilités d'erreurs ici)
	// if (server.set_pp(av[1], av[2]) != true){
	// 	// std::cout << "There is an error in arguments : ./ircserv <port> <password>" << std::endl;
	// 	return (1);
	// }
	
	// 4 initialiser (lancer?) le server
	// 5 lancer le programme dans une boucle (while (!end) end = c'est pas fini ici)
    
    return (0);
}

