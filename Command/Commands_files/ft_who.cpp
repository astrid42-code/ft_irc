/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_who.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:03:42 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/11 12:36:09 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"



//       Command: WHO
//    Parameters: [ <mask> [ "o" ] ]

//    The WHO command is used by a client to generate a query which returns
//    a list of information which 'matches' the <mask> parameter given by
//    the client.  In the absence of the <mask> parameter, all visible
//    (users who aren't invisible (user mode +i) and who don't have a
//    common channel with the requesting client) are listed.  The same
//    result can be achieved by using a <mask> of "0" or any wildcard which
//    will end up matching every visible user.

//    The <mask> passed to WHO is matched against users' host, server, real
//    name and nickname if the channel <mask> cannot be found.

//    If the "o" parameter is passed only operators are returned according
//    to the <mask> supplied.

//    Numeric Replies:

//            ERR_NOSUCHSERVER
//            RPL_WHOREPLY                  RPL_ENDOFWHO

//    Examples:

//    WHO *.fi                        ; Command to list all users who match
//                                    against "*.fi".

//    WHO jto* o                      ; Command to list all users with a
//                                    match against "jto*" if they are an
//                                    operator.

void who(Cmd &command)
{
	(void)command;
	std::cout << "who test" << std::endl;
/*    if (command.get_size() == 1){
		command._server->get_msg(ENDOFWHO, commqnd.get_user(), command);
		// a faire dans une boucle for pour mettre tous les users presents dans le channel?
	}
	else if (command.get_size() == 2){
		if (command.get_value()[1] == 'o'){
			command._server->get_msg(ENDOFWHO, commqnd.get_user(), command);
			// a faire  dans une boucle for pour mettre tous les users presents dans le channel?
			// et uniquement avec la liste des operateurs : comment le specifier?
		}
		else
			return;
	}
*/
}