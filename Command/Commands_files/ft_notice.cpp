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


void send_msg_to_user_not(User *usr, std::string str, Cmd &command, std::string chan)
{
	std::string msg = ":" + command._user->get_hostname() + " PRIVMSG " + chan + " :" + str + "\r\n";
	std::cout << "Sending :|" << msg << "| to :" << usr->get_nick() << std::endl;
	if (usr->find_mod("a"))
		return;
		// command._server->send_msg(RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), command._user->get_away()), command._sfd);
	else
		send(usr->get_sfd(), msg.c_str(), msg.length(), MSG_CONFIRM);
}

void send_msg_to_chan_not(Cmd &command, std::string destinataire)
{
	Channel *chan;
	std::map<int, User *>::iterator it;
	std::map<int, User *> users;

	std::cout << "________msg_to_chan________" << std::endl;
	chan = command._server->get_chan(destinataire.c_str());
	std::cout << "RETOUR" << std::endl;
	if (!chan || !chan->get_user(command._user->get_nick()))
		return;
		// command._server->send_msg(ERR_CANNOTSENDTOCHAN(command._user->get_hostname(), destinataire), command._sfd);
	else
	{
		users = chan->get_users();
		it = users.begin();
		// if (it != users.end())
		// 	std::cout << "" << std::endl;
		// else
		// 	std::cout << "no users" << std::endl;
		while (it != users.end())
		{
			std::cout << "User :" << command._user->get_nick() << std::endl;
			if (command._user != it->second)
				send_msg_to_user_not(it->second, command.get_value()[1], command, destinataire);
			it++;
		}
	}
	std::cout << "__________test__________" << std::endl;
}

void	notice(Cmd &command)
{
	User *user;

	std::cout << "notice test" << std::endl;
	std::string destinataire;
	destinataire = command.get_value().begin()[0];
	if (command.get_size() == 1 || (command.get_size() == 2 && command.get_value()[1].empty()))
		return;
		// command._server->send_msg(ERR_NOTEXTTOSEND(command._user->get_hostname()), command._sfd);
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
		}
		else
			return;
			// command._server->send_msg(ERR_NOSUCHNICK(command._user->get_hostname(), destinataire), command._sfd);
	}
	// std::cout << "destinataire : |" << destinataire.c_str() << "|" << std::endl;
}
