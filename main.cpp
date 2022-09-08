/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:31 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/07 17:28:59 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"
#include "Command/Cmd.hpp"
#include "User/User.hpp"

void	init_user(User &user)
{
	user.set_name("Tad amigo");
	user.set_mod("o");
	user.set_nick("tamigore");
	user.set_operator(1);
	user.set_pwd("1234567890");
	user.set_user("Tadeo");
}

int		main(int ac, char **av)
{
	(void)av;
	
	// if (ac != 3)
	// {
	// 	std::cout << "There is an error in arguments : ./ircserv <port> <password>" << std::endl;
	// 	return (1);
	// }
    
	// 1 creer un objet de la class Server server > définir ce que l'objet server contient
	// > un objet config dans lequel on récupère port et pwd (en vérifiant qu'ils suivent les règles de taille d'irc?)
	// + récupérer le user (prévoir qu'il peut y en avoir plsrs, les mettre dans un tableau / vector)
	// + pvr delete les users
	// + de même avec les channels

	Server server = Server();
	// server.init();
	// std::cout << "prout3 " << key << '\n';
	if (ac == 2)
	{
		Cmd		cmd;
		User	user;

		init_user(user);
		user.print();
		std::cout << av[1] << '\n';
		cmd.parse_cmd(av[1]);
		cmd.exec_cmd(cmd.get_key()); // recupere la string donnee au debut
	}
	
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

