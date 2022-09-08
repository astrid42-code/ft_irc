/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oper.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:00:36 by asgaulti          #+#    #+#             */
/*   Updated: 2022/08/30 17:07:42 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"

//  Command: OPER
//    Parameters: <name> <password>

//    A normal user uses the OPER command to obtain operator privileges.
//    The combination of <name> and <password> are REQUIRED to gain
//    Operator privileges.  Upon success, the user will receive a MODE
//    message (see section 3.1.5) indicating the new user modes.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              RPL_YOUREOPER
//            ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

//    Example:

//    OPER foo bar                    ; Attempt to register as an operator
//                                    using a username of "foo" and "bar"
//                                    as the password.


void oper(Cmd command){
    (void)command;
    std::cout << "oper test" << '\n';
}