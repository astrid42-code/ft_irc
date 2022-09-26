/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:31 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/24 18:09:52 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"
#include "Command/Cmd.hpp"
#include "User/User.hpp"

void	test()
{
	std::cout << "Welcome in my test" << std::endl;
	Server test("127.0.0.1", "6667");
	{
		Channel *chan_test = new Channel("#test");
		Channel *chan_blabla = new Channel("#blabla");
		test.set_chan(chan_test);
		test.set_chan(chan_blabla);
	}

	{
		User *dasanter = new User("Damien", "Santerre", "dasanter");
		User *tamigore = new User("Tadeo", "Amigorena", "tamigore");
		(*test.get_chan("#test")).set_user(dasanter);
		(*test.get_chan("#test")).set_user(dasanter);
		(*test.get_chan("#blabla")).set_user(tamigore);
	}
	(*test.get_chan("#test")).print();
	(*test.get_chan("#blabla")).print();
	std::cout << "_____________Server : ________________" << std::endl;
}

int		main(int ac, char **av)
{
	(void)av;
	if (ac == 3)
	{
		Server server = Server(av[1], av[2]);
		if (server.init() < 0)
		{
			std::cerr << "error in catching server info... need free and a real call to err." << std::endl;
		}
	}
	else
	{
		std::cout << "There is an error in arguments : ./ircserv <port> <password>" << std::endl;
		std::cout << "starting tests" << std::endl;
		// test();
		return (1);
	}
    return (0);
}

