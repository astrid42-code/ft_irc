#include "../Cmd.hpp"

void		chan_print(Channel *chan, Cmd &command, std::string arg)
{
	if (arg.compare("I") == 0)
	{
		std::cout << chan->get_mask() << std::endl;
		// need to send it to user.
		command._server->send_msg(RPL_INVITELIST(command._user->get_hostname(), chan->get_name(), chan->get_mask()), command._sfd);

	}
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
			command._server->send_msg(ERR_UMODEUNKNOWNFLAG(command._user->get_hostname()), command._sfd);
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

std::string	get_user_mode_string(User *user, std::string arg)
{
	(void)user;
	(void)arg;
	std::string res = "";

	if (user)
		res = user->get_mod();
	if (arg.find("+") != std::string::npos)
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
	else if (arg.find("-") != std::string::npos)
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
		std::cout << "I : " << res << std::endl;
	}
	return (res);
}

std::string	chan_mode_plus(Channel *chan, Cmd &command, std::string res, std::string arg, int *n)
{
	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg.find('k') != std::string::npos)
		{
			if (res.find('k') == std::string::npos)
			{
				if (*n + 1 < command.get_size() && !command.get_value()[*n + 1].empty())
				{
					chan->set_key(command.get_value()[++(*n)]);
					res += "k";
				}
			}
			else
				command._server->send_msg(ERR_KEYSET(command._user->get_hostname(), chan->get_name()), command._sfd);
		}
		if (arg.find('l') != std::string::npos && res.find('l') == std::string::npos)//&& (command._user->get_mod().find("o") || command._user->get_mod().find("O")))
		{
			if (*n + 1 < command.get_size() && !command.get_value()[*n + 1].empty())
			{
				chan->set_limit(atol(command.get_value()[++(*n)].c_str()));
				res += "l";
			}
		}
		if (arg.find('a') != std::string::npos && res.find('a') == std::string::npos)
			res = res.append("a");
		if (arg.find('i') != std::string::npos && res.find('i') == std::string::npos)
		{
			if (*n + 1 < command.get_size() && !command.get_value()[*n + 1].empty())
			{
				User *tmp = command._server->get_user(command.get_value()[++(*n)]);
				if (tmp)
				{
					command._server->send_msg(RPL_INVITING(command._user->get_hostname(), command.get_value()[++(*n)], chan->get_name()), command._sfd); // nick de l'invitant ou de l'invite???
					command._server->send_msg(RPL_INVITING(command._user->get_hostname(), command.get_value()[*n], chan->get_name()), tmp->get_sfd());
				}
			}
			res = res.append("i");
		}
		if (arg.find('I') != std::string::npos && res.find('I') == std::string::npos)
		{
			if (*n + 1 < command.get_size() && !command.get_value()[*n + 1].empty())
			{
				chan->set_mask(command.get_value()[++(*n)]);
				res = res.append("I");
			}
		}
		if (arg.find('m') != std::string::npos && res.find('m') == std::string::npos)
			res = res.append("m");
		if (arg.find('n') != std::string::npos && res.find('n') == std::string::npos)
			res = res.append("n");
		if (arg.find('q') != std::string::npos && res.find('q') == std::string::npos)
			res = res.append("q");
		if (arg.find('s') != std::string::npos && res.find('s') == std::string::npos)
			res = res.append("s");
		if (arg.find('r') != std::string::npos && res.find('r') == std::string::npos)
			res = res.append("r");
		if (arg.find('t') != std::string::npos && res.find('t') == std::string::npos)
			res = res.append("t");
	}
	return (res);
}

std::string	chan_mode_minus(Channel *chan,Cmd &command, std::string res, std::string arg, int *n)
{
	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg[i] == 'k' && res.find('k') != std::string::npos)//&& (command._user->get_mod().find("o") || command._user->get_mod().find("O")))
		{
			if ((*n + 1 < command.get_size()) && !command.get_value()[*n + 1].empty() && chan->get_key().compare(command.get_value()[*n + 1]) == 0)
			{	
				chan->set_key("");
				res = res.erase(res.find('k'), 1);
				(*n)++;
			}
		}
		if (arg[i] == 'l' && res.find('l') != std::string::npos)//&& (command._user->get_mod().find("o") || command._user->get_mod().find("O")))
		{
			chan->set_limit(4294967295);
			res = res.erase(res.find('l'), 1);
		}
		if (arg[i] == 'a' && res.find('a') != std::string::npos)
			res = res.erase(res.find('a'), 1);
		if (arg[i] == 'i' && res.find('i') != std::string::npos)
			res = res.erase(res.find('i'), 1);
		if (arg[i] == 'I' && res.find('I') != std::string::npos)
		{
			chan->set_mask("");
			res = res.erase(res.find('I'), 1);
		}
		if (arg[i] == 'm' && res.find('m') != std::string::npos)
			res = res.erase(res.find('m'), 1);
		if (arg[i] == 'n' && res.find('n') != std::string::npos)
			res = res.erase(res.find('n'), 1);
		if (arg[i] == 'q' && res.find('q') != std::string::npos)
			res = res.erase(res.find('q'), 1);
		if (arg[i] == 's' && res.find('s') != std::string::npos)
			res = res.erase(res.find('s'), 1);
		if (arg[i] == 'r' && res.find('r') != std::string::npos)
			res = res.erase(res.find('r'), 1);
		if (arg[i] == 't' && res.find('t') != std::string::npos)
			res = res.erase(res.find('t'), 1);
	}
	return (res);
}


std::string	get_chan_mode_string(Channel *chan, Cmd &command)
{
	std::string res = "";
	std::string arg;
	std::string param;

	if (chan)
		res = chan->get_mod();
	for (int i = 0; i < command.get_size(); i++)
	{
		arg = command.get_value()[i];
		if (i < command.get_size() - 1)
			param = command.get_value()[i + 1];
		if (arg.find("+") != std::string::npos)
			res = chan_mode_plus(chan, command, res, arg, &i);
		else if (arg.find("-") != std::string::npos)
			res = chan_mode_minus(chan, command, res, arg, &i);
		else
			chan_print(chan, command, arg);
	}
	return (res);
}

bool		mode_user(Cmd &command)
{
	if (command.get_value()[0].compare(command._user->get_nick()) == 0)
	{
		std::cout << "the user given in parameter match the user" << std::endl;
		if (command.get_size() == 1)
		{
			// std::cout << command._user->get_mod() << std::endl;// put this in a message to the client
			command._server->send_msg(RPL_UMODEIS(command._user->get_hostname(), command._user->get_user(), command._user->get_mod(), ""), command._sfd);
		}
		else
		{
			if (!check_mode_string(command, "-+aiwroOs"))
				return (false);
        	command._user->set_mod(get_user_mode_string(command._user, command.get_value()[1]));
		}
	}
	else
	{
		std::cout << "the user given in parameter invalid" << std::endl;
		command._server->send_msg(ERR_USERSDONTMATCH(command._user->get_hostname()), command._sfd);
		return (false);
	}
	return (true);
}

void		mode_chan(Cmd &command, Channel *chan)
{
	if (chan)
	{
		std::cout << "the channel given in parameter match the user" << std::endl;
		chan->print();
		if (command.get_size() == 1)
		{
			std::cout << chan->get_mod() << std::endl;// put this in a message to the client
			command._server->send_msg(RPL_CHANNELMODEIS(command._user->get_hostname(), chan->get_name(), chan->get_mod()), command._sfd);
		}
		else
		{
			if (!check_mode_string(command, "-+OovaimnqpsrtklbI")) // e = exeption mask (useless ?)
				return ;
			chan->set_mod(get_chan_mode_string(chan, command));
		}
	}
	else
	{
		std::cout << "the channel given in parameter invalid" << std::endl;
		command._server->send_msg(ERR_USERNOTINCHANNEL(command._user->get_hostname(), command._user->get_nick(),command.get_value()[0]), command._sfd);
	}
}

void		mode(Cmd &command)
{
	std::cout << "ft_mode start" << std::endl;
	if (command.get_size() >= 1)
	{
		if (command.get_value()[0].find("#") == 0)
			mode_chan(command, command._user->get_channel(command.get_value()[0]));
		else
		{
			if (!mode_user(command))
				return ;
			command._user->print();
		}
		command._server->send_msg(RPL_UMODEIS(command._user->get_hostname(), command._user->get_user(), command._user->get_mod(), ""), command._sfd);
	}
	else
	{
		std::cout << "err need more params" << std::endl;
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
	}
}