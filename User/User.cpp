/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:33:25 by asgaulti          #+#    #+#             */
/*   Updated: 2022/06/14 12:37:19 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

namespace irc
{
//}
	
User::User(){
	// parser avec regles user (voir notes)
	// msg de bienvenue reprenant le login user?
	// stocker les differentes infos users dans une map ? (login, pwd, autre?)
}

User::~User(){
	// delete les differents users	
}

User & operator=(const User & user_cp){
	_name = user_cp._name;
	return (*this);
}

std::string User::get_user() const{
	return (_name);
}

std::string User::get_pwd() const{
	return (_pwd);
}

void	User::set_user(std::string name){
	_name = name;
}

void	User::set_pwd(std::string pwd){
	_pwd = pwd;
}

// a faire avant de stocker le user dans une map/un vector
bool	check_user(){
	if (_user.size() > 9){
		std::cout << "Login is too long : 9 characters max" << std::endl; 
		return (false);
	}
	// comparer ensuite avec les autres logins déjà connectés :
	// msg  a l'inscription en cas de doublon 
	// std::cout << "*** Nickname " << _name << "" is already in use, type /nick newnick to use another." << std::endl;
	// accepte le login doublon mais possibilite de changer avec la cmd donnee
	// donc prévoir de modifier le vector (et la map dans laquelle il est stocké?) 
	// donc pas à faire ici mais à lancer dans une autre fct externes (dans le server?)

	return (true);
}
}