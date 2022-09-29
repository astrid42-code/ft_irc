/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invite.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:55:49 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/29 18:49:45 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


// Message INVITE
// Paramètres : <nick> <nom du chan>
// Réponses possibles : ERR_NEEDMOREPARAMS (461), ERR_NOSUCHNICK (401), ERR_NOTONCHANNEL (442), ERR_USERONCHANNEL (443), ERR_CHANOPRIVSNEEDED (482), RPL_INVITING(341)

// Permet d'inviter un utilisateur sur un chan. 


//       Command: INVITE
//    Parameters: <nickname> <channel>

//    The INVITE command is used to invite a user to a channel.  The
//    parameter <nickname> is the nickname of the person to be invited to
//    the target channel <channel>.  There is no requirement that the
//    channel the target user is being invited to must exist or be a valid
//    channel.  However, if the channel exists, only members of the channel
//    are allowed to invite other users.  When the channel has invite-only
//    flag set, only channel operators may issue INVITE command.

//    Only the user inviting and the user being invited will receive
//    notification of the invitation.  Other channel members are not
//    notified.  (This is unlike the MODE changes, and is occasionally the
//    source of trouble for users.)

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
//            ERR_NOTONCHANNEL                ERR_USERONCHANNEL
//            ERR_CHANOPRIVSNEEDED
//            RPL_INVITING                    RPL_AWAY

//    Examples:

//    :Angel!wings@irc.org INVITE Wiz #Dust

//                                    ; Message to WiZ when he has been
//                                    invited by user Angel to channel
//                                    #Dust

//    INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
//                                    #Twilight_zone


// msgs erreurs ok, mais a verifier avec nc pour l'affichage exact
// + tester avec deux utilisateurs au moins


void invite(Cmd &command)
{
	
    std::cout << "invite test" << std::endl;
    if (command.get_value().size() != 2)
	{
		command._server->send_msg(ERR_NEEDMOREPARAMS(command._user->get_hostname(), command.get_key()), command._sfd);
		return ;
	}
    else if (!command._server->get_user(command.get_value()[0]))
		// ou?? : command.get_value()[0] != command._user->get_nick()) // a revoir > pas la bonne comparaison
	{
		command._server->send_msg(ERR_NOSUCHNICK(command._user->get_hostname(), command.get_value()[0]), command._sfd);
		return ;
	}
	else if (!command._user->get_channel(command.get_value()[1])) // checker le nom du channel renvoye ici
	{
		command._server->send_msg(ERR_NOTONCHANNEL(command._user->get_hostname(), command.get_value()[1]), command._sfd);
		return ;
	}
	else if (command._server->get_user(command.get_value()[0])->get_channel(command.get_value()[1]))
	{
		command._server->send_msg(ERR_USERONCHANNEL(command._user->get_hostname(), command.get_value()[0], command.get_value()[1]), command._sfd);
		return ;
	}
	if (command._user->find_mod("a"))
	{
		command._server->send_msg(RPL_AWAY(command._user->get_hostname(), command._user->get_nick(), command._user->get_away()), command._sfd);
		return ;
	}
    if (command._server->get_chan(command.get_value()[1])->get_mod().find('i'))
	{
		if (!command._user->find_mod("o"))
		{
			command._server->send_msg(ERR_CHANOPRIVSNEEDED(command._user->get_hostname(), command.get_value()[1]), command._sfd);
			return ;
		}
	}
    command._server->send_msg(RPL_INVITING(command._user->get_hostname(), command.get_value()[1], command.get_value()[0]), command._sfd);
}