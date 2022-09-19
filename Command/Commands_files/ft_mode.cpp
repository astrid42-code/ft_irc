#include "../Cmd.hpp"

void	mode(Cmd &command)
{
	(void)command;
	std::cout << "ft_mode start" << std::endl;
	if (command.get_size() == 1 || command.get_size() == 2)
	{
		if (command.get_value()[0].compare(command._user->get_nick()) == 0)
		{
			std::cout << "the user given in parameter match the user" << std::endl;
			if (command.get_size() == 1)
				std::cout << command._user->get_mod() << std::endl;// put this in a message to the client
			else
			{
				std::string::iterator it = command.get_value()[1].begin();
				while (it != command.get_value()[1].end())
				{
					if (*it != '*' && *it != '-' && *it != '+' && *it != 'i' && *it != 'o' && *it != 'O' && *it != 'a' && *it != 'w' && *it != 'r' && *it != 's')
					{
						std::cout << "the user given in parameter invalid" << std::endl;
            			command._server->get_msg(ERR_UMODEUNKNOWNFLAG, NULL, command);
					}
					it++;
				}
				if (command.get_value()[1].find("+") != std::string::npos && command.get_value()[1].find("-") == std::string::npos)
				{
					std::cout << "+ opt" << std::endl;
            		// command._user->find_mod(command.get_value()[1].find())
					command._server->get_msg(RPL_UMODEIS, NULL, command);
				}
				else if (command.get_value()[1].find("+") == std::string::npos && command.get_value()[1].find("-") != std::string::npos)
				{
					std::cout << "- opt" << std::endl;
					command._server->get_msg(RPL_UMODEIS, NULL, command);
				}
				else
				{
					std::cout << "the user given in parameter invalid" << std::endl;
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
}