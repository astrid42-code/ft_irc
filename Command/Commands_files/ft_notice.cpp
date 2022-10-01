#include "../Cmd.hpp"

// 3.3.2 Notice

//       Command: NOTICE
//    Parameters: <msgtarget> <text>

//    The NOTICE command is used similarly to PRIVMSG.  The difference
//    between NOTICE and PRIVMSG is that automatic replies MUST NEVER be
//    sent in response to a NOTICE message.  This rule applies to servers
//    too - they MUST NOT send any error reply back to the client on
//    receipt of a notice.  The object of this rule is to avoid loops
//    between clients automatically sending something in response to
//    something it received.

//    This command is available to services as well as users.

//    This is typically used by services, and automatons (clients with
//    either an AI or other interactive program controlling their actions).

//    See PRIVMSG for more details on replies and examples.

void send_msg_to_chan_not(Cmd &command, std::string destinataire)
{
	Channel *chan;
	std::map<int, User *>::iterator it;
	std::map<int, User *> users;

	chan = command._server->get_chan(destinataire.c_str());
	if (!chan || !chan->get_user(command._user->get_nick()))
		return;
	else
	{
		users = chan->get_users();
		it = users.begin();
		while (it != users.end())
		{
			if (command._user != it->second)
			{
				if (it->second->find_mod("a"))
					command._server->send_msg(RPL_AWAY(command._user->get_hostname(), it->second->get_nick(), command._user->get_away()), command._sfd);
				if (!it->second->find_mod("i"))
					command._server->send_msg(NOTICE(command._user->get_hostname(), chan->get_name(), command.get_value()[1]),command._server->get_user(destinataire)->get_sfd());
			}
			it++;
		}
	}
}

void	notice(Cmd &command)
{
	User		*user;
	std::string	destinataire;

	std::cout << "notice test" << std::endl;
	if (command.get_size() <= 1 || (command.get_size() == 2 && command.get_value()[1].empty()))
		return;
	destinataire = command.get_value().begin()[0];
	if (destinataire.c_str()[0] == '#')
	{
		std::cout << "msg_to_chan" << std::endl;
		send_msg_to_chan_not(command, destinataire);
	}
	else
	{
		std::cout << "msg_to_user" << std::endl;
		if ((user = command._server->get_user(destinataire)) != NULL)
		{
			if (user->find_mod("a"))
				command._server->send_msg(RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), command._user->get_away()), command._sfd);
			if (!user->find_mod("i"))
				command._server->send_msg(NOTICE(command._user->get_hostname(), destinataire,command.get_value()[1]),command._server->get_user(destinataire)->get_sfd());

		}
	}
}
