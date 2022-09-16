/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_privmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:17 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/11 12:36:09 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"


//       Command: PRIVMSG
//    Parameters: <msgtarget> <text to be sent>

//    PRIVMSG is used to send private messages between users, as well as to
//    send messages to channels.  <msgtarget> is usually the nickname of
//    the recipient of the message, or a channel name.

//    The <msgtarget> parameter may also be a host mask (#<mask>) or server
//    mask ($<mask>).  In both cases the server will only send the PRIVMSG
//    to those who have a server or host matching the mask.  The mask MUST
//    have at least 1 (one) "." in it and no wildcards following the last
//    ".".  This requirement exists to prevent people sending messages to
//    "#*" or "$*", which would broadcast to all users.  Wildcards are the
//    '*' and '?'  characters.  This extension to the PRIVMSG command is
//    only available to operators.

//    Numeric Replies:

//            ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
//            ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
//            ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
//            ERR_NOSUCHNICK
//            RPL_AWAY

void send_msg_to_user(User *usr, std::vector<std::string> str)
{
    std::string msg;
    int i = 0;
    while (!str[i].empty())
    {
        msg.append(str[i]);
        i++;
    
    }
    std::cout << "Sending :|" << msg << "| to :" << usr->get_nick() << std::endl;
}

void send_msg_to_chan(Cmd &command, std::string destinataire)
{
    Channel *chan;
    Server *serv;
    std::map<int, User *>::iterator it;
    std::map<int, User *> Users;

    std::cout << "________msg_to_chan________" << std::endl;
    serv = command._server;
    chan = serv->get_chan(destinataire.c_str());
    std::cout << "RETOUR" << std::endl;
    if (!serv->get_chan(destinataire.c_str()))
    {
        std::cout << "le chan n existe pas" << std::endl;
        return;
    }
    Users = chan->get_users();
    it = Users.begin();
    if (it != Users.end())
        std::cout << "diff" << std::endl;
    else
    {
        std::cout << "equal" << std::endl;
    }
    while (it != Users.end())
    {
        std::cout << "User :" << command._user->get_nick() << std::endl;
        if (command._user != it->second)
            send_msg_to_user(it->second, command.get_value());
        it++;
    }
}

void privmsg(Cmd &command)
{
    std::cout << "privmsg test" << std::endl;
    std::string destinataire;
    destinataire = command.get_value().begin()[0];
    if (destinataire.c_str()[0] == '#')
    {
        std::cout << "msg_to_chann" << std::endl;
        send_msg_to_chan(command, destinataire);
    }
    std::cout << "destinataire : |" << destinataire.c_str()[0] << "|" << std::endl;
   // command.print();
    // necessite d'etre dans un channel (?)
    // command.get_value()[0] la target = le user ou le channel qui recoit le msg
    // command.get_value()[1] le msg a envoyer a la target
    // command._server->get_msg(command.get_value()[1], NULL, command)
    // necessaire de chercher avant get_msg quelle est la target? comment la preciser ensuite (puisque ca peut etre user ou channel)?
}