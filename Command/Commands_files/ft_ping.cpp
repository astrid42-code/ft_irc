#include "../Cmd.hpp"
#include "../../Server/Server.hpp"


// Command: PING
//    Parameters: <server1> [ <server2> ]

void ping(Cmd &command)
{
	if (std::time(NULL) - command._server->get_time() > TIME_LIMIT)
	{
		command._server->send_msg(PING(), command._sfd);
		command._server->set_time(std::time(NULL));
	}
}

// Command: PONG
//    Parameters: <server> [ <server2> ]

void	pong(Cmd &command)
{
	if (!command.get_value().size())
		command._server->send_msg(ERR_NOORIGIN(command._user->get_hostname()), command._sfd);
	else if (command.get_value().size() == 1)
	{
		if (command.get_value()[0].compare(command._user->get_nick()) == 0)
			command._server->send_msg(PONG(), command._sfd);
	}
	else if (command.get_value().size() == 2){
		command._server->send_msg(ERR_NOSUCHSERVER(command._user->get_hostname(), command.get_value()[1]), command._sfd);
		return;
	}
}