/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:31 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:29:11 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"
#include "Command/Cmd.hpp"
#include "User/User.hpp"
#include <signal.h>

void test()
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
	// (*test.get_chan("#test")).print();
	// (*test.get_chan("#blabla")).print();
	std::cout << "_____________Server : ________________" << std::endl;
}

Server *getset_serv(Server *server)
{

	static Server *serv;
	if (server)
	{
		serv = server;
		return (serv);
	}
	else
	{
		return (serv);
	}
}

void sig_handler(int sig)
{
	std::map<int, User *> *users;
	std::map<std::string, Channel *>	*chans;
	Server *serv = getset_serv(NULL);
	if (serv && sig == SIGINT)
	{
		users = serv->get_users();
		chans = serv->get_chans();
		std::cout << "Closing Connections" << std::endl;
		for (std::map<int, User *>::iterator it = users->begin(); it != users->end(); it++)
		{
			serv->send_msg(QUIT(it->second->get_hostname(), "Server is Closing ... Sorry :/ "), it->second->get_sfd());
			close(it->second->get_sfd());
			delete it->second;
		}
		for (std::map<std::string, Channel *>::iterator it = chans->begin(); it != chans->end(); it++)
		{
			delete it->second;
		}
		delete serv;
		exit(0);
	}
}

int main(int ac, char **av)
{
	(void)av;
	if (ac == 3)
	{
		Server *server = new Server(av[1], av[2]);
		getset_serv(server);
		signal(SIGINT, sig_handler);
		if (server->init() < 0)
		{
			delete server;
			//std::cerr << "error in catching server info... need free and a real call to err." << std::endl;
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
