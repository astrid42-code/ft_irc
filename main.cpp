/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:31 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/11 12:37:46 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"
#include "Command/Cmd.hpp"
#include "User/User.hpp"

void	test()
{
	Server test("127.0.0.1", "6667");
	Channel test("#test");
	test.set_chan(test);
}

int		main(int ac, char **av)
{
	(void)av;
	if (ac == 3)
	{
		Server server = Server(av[1], av[2]);
		server.init();
	}
	else
	{
		std::cout << "There is an error in arguments : ./ircserv <port> <password>" << std::endl;
		std::cout << "starting tests" << std::endl;
		
		return (1);
	}
    
	// 1 creer un objet de la class Server server > définir ce que l'objet server contient
	// > un objet config dans lequel on récupère port et pwd (en vérifiant qu'ils suivent les règles de taille d'irc?)
	// + récupérer le user (prévoir qu'il peut y en avoir plsrs, les mettre dans un tableau / vector)
	// + pvr delete les users
	// + de même avec les channels

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

