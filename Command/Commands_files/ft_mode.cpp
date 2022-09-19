#include "../Cmd.hpp"

std::string	get_mode_string(User *user, std::string arg, bool opt)
{
	std::string res = user->get_mod();
	
	if (opt == 1)
	{
		if (arg.find('i') >= 0 && res.find('i') == std::string::npos)
			res = res.append("i");
		if (arg.find('w') >= 0 && res.find('w') == std::string::npos)
			res = res.append("w");
		if (arg.find('r') >= 0 && res.find('r') == std::string::npos)
			res = res.append("r");
		if (arg.find('s') >= 0 && res.find('s') == std::string::npos)
			res = res.append("s");
	}
	else
	{
		if (arg.find('i') >= 0 && res.find('i') >= 0)
			res = res.erase(res.find('i'), 1);
		if (arg.find('w') >= 0 && res.find('w') >= 0)
			res = res.erase(res.find('w'), 1);
		if (arg.find('o') >= 0 && res.find('o') >= 0)
			res = res.erase(res.find('o'), 1);
		if (arg.find('O') >= 0 && res.find('O') >= 0)
			res = res.erase(res.find('O'), 1);
		if (arg.find('s') >= 0 && res.find('s') >= 0)
			res = res.erase(res.find('s'), 1);
	}
	return (res);
}

bool		check_mode_string(Cmd &command)
{
	std::string::iterator it = command.get_value()[1].begin();

	while (it != command.get_value()[1].end())
	{
		if (*it != '*' && *it != '-' && *it != '+' && *it != 'i' && *it != 'o' && *it != 'O' && *it != 'a' && *it != 'w' && *it != 'r' && *it != 's')
		{
			std::cout << "the modes given in parameter are invalid" << std::endl;
			command._server->get_msg(ERR_UMODEUNKNOWNFLAG, NULL, command);
			return (0);
		}
		it++;
	}
	return (1);
}

void		mode(Cmd &command)
{
	std::cout << "ft_mode start" << std::endl;
	if (command.get_size() == 1 || command.get_size() == 2)
	{
		if (command.get_value()[0].compare(command._user->get_nick()) == 0)
		{
			std::cout << "the user given in parameter match the user" << std::endl;
			if (command.get_size() == 1)
			{
				std::cout << command._user->get_mod() << std::endl;// put this in a message to the client
				command._server->get_msg(RPL_UMODEIS + command._user->get_mod(), NULL, command);
			}
			else
			{
				if (!check_mode_string(command))
					return ;
				if (command.get_value()[1].find("+") != std::string::npos && command.get_value()[1].find("-") == std::string::npos)
				{
					std::cout << "+ opt" << std::endl;
            		command._user->set_mod(get_mode_string(command._user, command.get_value()[1], 1));
				}
				else if (command.get_value()[1].find("+") == std::string::npos && command.get_value()[1].find("-") != std::string::npos)
				{
					std::cout << "- opt" << std::endl;
					command._user->set_mod(get_mode_string(command._user, command.get_value()[1], 0));
				}
				else
				{
					std::cout << "the user given in parameter isn't correct" << std::endl;
            		command._server->get_msg(ERR_UMODEUNKNOWNFLAG, NULL, command);
				}
			}
		}
		else
		{
			std::cout << "the user given in parameter invalid" << std::endl;
			command._server->get_msg(ERR_USERSDONTMATCH, NULL, command);
		}
	}
	else
	{
		std::cout << "wrong number of arguments" << std::endl;
		command._server->get_msg(ERR_NEEDMOREPARAMS(), NULL, command);
	}
	command._user->print();
}