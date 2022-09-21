#include "../Cmd.hpp"

std::string	get_mode_string(Channel *chan, User *user, std::string arg, bool opt)
{
	std::string res;

	if (chan)
		res = chan->get_mod();
	if (user)
		res = user->get_mod();
	if (opt == 1)
	{
		if (arg.find('i') != std::string::npos && res.find('i') == std::string::npos)
			res = res.append("i");
		if (arg.find('w') != std::string::npos && res.find('w') == std::string::npos)
			res = res.append("w");
		if (arg.find('r') != std::string::npos && res.find('r') == std::string::npos)
			res = res.append("r");
		if (arg.find('s') != std::string::npos && res.find('s') == std::string::npos)
			res = res.append("s");
	}
	else
	{
		if (arg.find('i') != std::string::npos && res.find('i') != std::string::npos)
			res = res.erase(res.find('i'), 1);
		if (arg.find('w') != std::string::npos && res.find('w') != std::string::npos)
			res = res.erase(res.find('w'), 1);
		if (arg.find('o') != std::string::npos && res.find('o') != std::string::npos)
			res = res.erase(res.find('o'), 1);
		if (arg.find('O') != std::string::npos && res.find('O') != std::string::npos)
			res = res.erase(res.find('O'), 1);
		if (arg.find('s') != std::string::npos && res.find('s') != std::string::npos)
			res = res.erase(res.find('s'), 1);
	}
	return (res);
}

bool		check_mode_string(Cmd &command, std::string mods)
{
	std::string::iterator	it = command.get_value()[1].begin();
	int						i;

	i = 0;
	while (it != command.get_value()[1].end())
	{
		if (mods.find(*it) == std::string::npos)
		{
			std::cout << "the modes given in parameter are invalid" << std::endl;
			command._server->get_msg(ERR_UMODEUNKNOWNFLAG, NULL, command);
			return (0);
		}
		if (i == 1 && *it == '+')
			return (0);
		else if (i == 2 && *it == '-')
			return (0);
		if (*it == '-')
			i = 1;
		else if (*it == '+')
			i = 2;
		it++;
	}
	return (1);
}

void		mode_user(Cmd &command)
{
	if (command.get_value()[0].compare(command._user->get_nick()) == 0)
	{
		std::cout << "the user given in parameter match the user" << std::endl;
		if (command.get_size() == 1)
		{
			std::cout << command._user->get_mod() << std::endl;// put this in a message to the client
			command._server->get_msg(RPL_UMODEIS, NULL, command);
		}
		else
		{
			if (!check_mode_string(command, "-+aiwroOs"))
				return ;
			if (command.get_value()[1].find("+") != std::string::npos)
			{
				std::cout << "+ opt" << std::endl;
        		command._user->set_mod(get_mode_string(NULL, command._user, command.get_value()[1], 1));
			}
			else if (command.get_value()[1].find("-") != std::string::npos)
			{
				std::cout << "- opt" << std::endl;
				command._user->set_mod(get_mode_string(NULL, command._user, command.get_value()[1], 0));
			}
		}
	}
	else
	{
		std::cout << "the user given in parameter invalid" << std::endl;
		command._server->get_msg(ERR_USERSDONTMATCH, NULL, command);
	}
}

void		mode_chan(Cmd &command)
{
	Channel *chan = command._user->get_channel(command.get_value()[0]);

	if (chan)
	{
		std::cout << "the channel given in parameter match the user" << std::endl;
		chan->print();
		if (command.get_size() == 1)
		{
			std::cout << chan->get_mod() << std::endl;// put this in a message to the client
			command._server->get_msg(RPL_CHANNELMODEIS(chan->get_name(), chan->get_mod(), "-+OovaimnqpsrtklbeI"), NULL, command);
		}
		else
		{
			if (!check_mode_string(command, "-+OovaimnqpsrtklbeI"))
				return ;
			if (command.get_value()[1].find("+") != std::string::npos)
			{
				std::cout << "+ opt" << std::endl;
        		chan->set_mod(get_mode_string(chan, NULL, command.get_value()[1], 1));
			}
			else if (command.get_value()[1].find("-") != std::string::npos)
			{
				std::cout << "- opt" << std::endl;
				chan->set_mod(get_mode_string(chan, NULL, command.get_value()[1], 0));
			}
		}
	}
	else
	{
		std::cout << "the channel given in parameter invalid" << std::endl;
		command._server->get_msg(ERR_USERNOTINCHANNEL(command._user->get_nick(), command.get_value()[0]), NULL, command);
	}
}

void		mode(Cmd &command)
{
	std::cout << "ft_mode start" << std::endl;
	if (command.get_size() == 1 || command.get_size() == 2)
	{
		if (command.get_value()[0][0] == '#')
		{
			mode_chan(command);
			command._user->get_channel(command.get_value()[0])->print();
		}
		else
		{
			mode_user(command);
			command._user->print();
		}
	}
	else
	{
		std::cout << "wrong number of arguments" << std::endl;
		command._server->get_msg(ERR_NEEDMOREPARAMS(), NULL, command);
	}
}