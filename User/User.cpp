/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:33:25 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/07 12:54:55 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
	
User::User() : _user("toto"), _name("titi toto"), _nick("titi"), _pwd("pwd"), _mod(""), _operator(0)
{
	std::cout << "User create by default." << std::endl;
	// parser avec regles user (voir notes)
	// msg de bienvenue reprenant le login user? <apparament dans une autre fonction (utilisation de la commande USER pour set les informations...)>
	// stocker les differentes infos users dans une map ? (login, pwd, autre?)
}

User::~User()
{
	// delete les differents users	
}

User & User::operator=(const User & user_cp)
{
	if (!check_nick(user_cp._nick))
	{
		std::cout << "New user nickname incorrect..." << std::endl;
		return (*this);
	}
	_user = user_cp._user;
	_name = user_cp._name;
	_nick = user_cp._nick;
	_pwd = user_cp._pwd;
	_mod = user_cp._mod;
	_operator = user_cp._operator;
	return (*this);
}

std::string User::get_user() const
{
	return (_user);
}

std::string User::get_name() const
{
	return (_name);
}

std::string User::get_nick() const
{
	return (_nick);
}

std::string User::get_pwd() const
{
	return (_pwd);
}

std::string User::get_mod() const
{
	return (_mod);
}

int	User::get_operator() const
{
	return (_operator);
}

void	User::set_user(std::string user)
{
	_user = user;
}

void	User::set_name(std::string name)
{
	_name = name;
}

void	User::set_nick(std::string nick)
{
	_nick = nick;
}

void	User::set_pwd(std::string pwd)
{
	_pwd = pwd;
}

void	User::set_operator(int op)
{
	_operator = op;
}

void	User::set_mod(std::string mod)
{
	if (!_mod.find("a") && mod.find("a"))
		_mod += "a";
	else if (!_mod.find("i") && mod.find("i"))
		_mod += "i";
	else if (!_mod.find("w") && mod.find("w"))
		_mod += "w";
	else if (!_mod.find("r") && mod.find("r"))
		_mod += "r";
	else if (!_mod.find("o") && mod.find("o"))
		_mod += "o";
	else if (!_mod.find("O") && mod.find("O"))
		_mod += "O";
	else if (!_mod.find("s") && mod.find("s"))
		_mod += "s";
/*
		a - user is flagged as away;
		i - marks a users as invisible;
		w - user receives wallops;
		r - restricted user connection;
		o - operator flag;
		O - local operator flag;
		s - marks a user for receipt of server notices.
*/
}

// a faire avant de stocker le user dans une map/un vector
bool	User::check_nick(std::string new_nick)
{
	if (_nick.size() > 9)
	{
		std::cout << "Login is too long : 9 characters max" << std::endl; 
		return (false);
	}
	else if (_nick.compare(new_nick) == 0)
	{
		std::cout << "Nickname is already used." << std::endl; 
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

bool	User::find_mod(std::string mod)
{
	if (_mod.find(mod) == 0)
		return (1);
	return (0);
}

void	User::print(void) const
{
	std::cout << "user :" + _user << " | name:" + _name << " | nick:" + _nick << " | pwd:" + _pwd << " | operator:" + SSTR(_operator) << " | mod:" + _mod << std::endl;
}