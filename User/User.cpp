/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:33:25 by asgaulti          #+#    #+#             */
/*   Updated: 2022/09/30 11:12:49 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
	
User::User() : _user("toto"), _name("titi toto"), _nick("titi"), _mod(""),  _host(""), _valid(0)
{
	// std::cout << "User create by default." << std::endl;
	// parser avec regles user (voir notes)
	// msg de bienvenue reprenant le login user? <apparament dans une autre fonction (utilisation de la commande USER pour set les informations...)>
	// stocker les differentes infos users dans une map ? (login, pwd, autre?)
}

User::User(std::string prenom, std::string name, std::string nickname)
{
	_user = prenom;
	_name = name;
	_nick = nickname;
	_valid = 0;
	_vchan = new std::vector<Channel *>();
	// std::cout << "User create by default." << std::endl;
	// parser avec regles user (voir notes)
	// msg de bienvenue reprenant le login user? <apparament dans une autre fonction (utilisation de la commande USER pour set les informations...)>
	// stocker les differentes infos users dans une map ? (login, pwd, autre?)
}

User::User(std::string nickname, int sdf)
{
	_nick = nickname;
	_sfd = sdf;
	_valid = 0;
	_vchan = new std::vector<Channel *>();
	// std::cout << "User create by default." << std::endl;
	// parser avec regles user (voir notes)
	// msg de bienvenue reprenant le login user? <apparament dans une autre fonction (utilisation de la commande USER pour set les informations...)>
	// stocker les differentes infos users dans une map ? (login, pwd, autre?)
}

User::User(int sdf)
{
	_sfd = sdf;
	_valid = 0;
	_vchan = new std::vector<Channel *>();
}

User::~User()
{
	std::cout << "User destroyed..." << std::endl;
	delete (_vchan);
}

User					&User::operator=(const User & user_cp)
{
	if (!check_nick(user_cp._nick))
	{
		std::cout << "New user nickname incorrect..." << std::endl;
		return (*this);
	}
	_user = user_cp._user;
	_name = user_cp._name;
	_nick = user_cp._nick;
	_mod = user_cp._mod;
	_valid = user_cp._valid;
	return (*this);
}

bool					User::operator==(const User & user_cp)
{
	if (_user == user_cp._user && _name == user_cp._name && _nick == user_cp._nick
		&& _mod == user_cp._mod && _valid == user_cp._valid)
		return (true);
	return (false);
}

std::string				User::get_user() const
{
	return (_user);
}

std::string				User::get_name() const
{
	return (_name);
}

std::string				User::get_nick() const
{
	return (_nick);
}

std::string				User::get_host() const
{
	return (_host);
}

std::string				User::get_mod() const
{
	return (_mod);
}

int						User::get_sfd() const
{
	return (_sfd);
}

int						User::get_valid() const
{
	return (_valid);
}

Channel					*User::get_channel(std::string name)
{
	std::vector<Channel *>::iterator	it;

	for (it = _vchan->begin(); it != _vchan->end(); it++)
	{
		// std::cout << "key " << name << " get_key " << (*it)->get_key() << std::endl;
		if ((*it)->get_key().compare(name) == 0)
			return (*it);
	}
	return (NULL);
}

std::string				User::get_channel_name()
{
	std::vector<Channel *>::iterator	it;
	std::string							names = "";

	for (it = _vchan->begin(); it != _vchan->end(); it++)
	{
		names.append((*it)->get_key());
	}
	return (names);
}

std::vector<Channel *>	*User::get_chans() const
{
	return (_vchan);
}

std::string				User::get_hostname() const
{
	return (_nick + "!" + _user + "@" + _host);
}

std::string				User::get_away() const
{
	return (_away);
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
	std::cout << "set nick" << std::endl;
	_nick = nick;
}

void	User::set_host(std::string host)
{
	_host = host;
}

void	User::set_valid(int op)
{
	_valid = op;
}

void	User::set_sfd(int sfd)
{
	_sfd = sfd;
	std::cout << "get sfd " << get_sfd() << std::endl;
}

void	User::set_mod(std::string mod)
{
	_mod = mod;
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

void	User::set_chan(Channel &chan)
{
	std::vector<Channel *>::iterator it;
	// std::cout << "coucou 1 set_chan user" << std::endl;
	
	_vchan->push_back(&chan);
	
	for (it = _vchan->begin(); it != _vchan->end(); it++){
		std::cout << "it chan user : " << *it << std::endl;
		
	}
}

void	User::set_away(std::string msg)
{
	_away = msg;
}

// a faire avant de stocker le user dans une map/un vector
bool	User::check_nick(std::string new_nick)
{
	if (_nick.size() > 9)
	{
		std::cout << "Login is too long : 9 characters max" << std::endl; 
		return (false);
	}
	else if (_nick.compare(new_nick) == 0 || _nick.compare("anonymous") == 0)
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
	if (_mod.find(mod) != std::string::npos)
		return (1);
	return (0);
}

void	User::print(void) const
{
	std::cout << "user :" + _user << " | name:" + _name << " | nick:" + _nick << " | operator:" + SSTR(_valid) << " | mod:" + _mod  << " | sfd:" + SSTR(_sfd) << std::endl;
}

std::vector<Channel *>::iterator	User::it_chan(std::string chan_name)
{
	std::vector<Channel *>::iterator	it;
	
	std::cout << "searching for chan pos :" << chan_name << std::endl;
	for (it = _vchan->begin(); it < _vchan->end(); it++)
	{
		if ((*it)->get_name().compare(chan_name) == 0)
			return it;
	}
	return it;
}

void	User::remove_chan(Channel * channel)
{
	std::vector<Channel *>::iterator it;
	
	if (!channel)
		return ;
	for (it = _vchan->begin(); it != _vchan->end(); it++)
	{
		if (*it == channel)
		{
			std::cout << "remove_chan channel  = " << (*it)->get_name() << std::endl;
			_vchan->erase(it);
			return;
		}
	}
}

std::ostream	&operator<<(std::ostream &os, const User &user_cp)
{
	os << "user :" + user_cp.get_user() + " | name:" + user_cp.get_name() + " | nick:" + user_cp.get_nick() + " | operator:" + SSTR(user_cp.get_valid()) + " | mod:" + user_cp.get_mod() + " | sfd:" + SSTR(user_cp.get_sfd());
	return (os);
}