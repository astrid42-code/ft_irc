/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:49:53 by asgaulti          #+#    #+#             */
/*   Updated: 2022/10/01 17:28:30 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : _name("NoName"), _ID("toto"), _mod(""), _topic(""), _key("")
{}

Channel::Channel(std::string name)
{
	_name = name;
}

Channel::~Channel()
{}

Channel & Channel::operator=(const Channel & ch_cp)
{
	this->_name = ch_cp._name;
	this->_users = ch_cp._users;
	this->_ID = ch_cp._ID;
	this->_mod = ch_cp._mod;
	return (*this);
}

bool Channel::operator==(const Channel & ch_cp)
{
	if (_name != ch_cp._name)
		return (false);
	if (_ID != ch_cp._ID)
		return (false);
	if (_mod != ch_cp._mod)
		return (false);
	return (true);
}


std::string					Channel::get_name() const
{
	return (_name);
}

std::string					Channel::get_ID() const
{
	return (_ID);
}

std::string					Channel::get_mod() const
{
	return (_mod);
}

std::map<int, User *>	Channel::get_users() const
{
	return (_users);
}

User						*Channel::get_user(int key)
{
	std::map<int, User *>::iterator it;
	
	it = _users.find(key);
	if (it == _users.end())
		return (NULL);
	return (it->second);
}

User						*Channel::get_user(std::string nick)
{
	std::map<int, User *>::iterator it;
	
	for (it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->get_nick().compare(nick) == 0)
			return (it->second);
	}
	return (NULL);
}

std::string		Channel::get_topic() const
{
	return (_topic);
}

std::string		Channel::get_key() const
{
	return (_key);
}

unsigned int	Channel::get_limit() const
{
	return (_limit);
}

std::string		Channel::get_mask() const
{
	return (_mask);
}


void			Channel::set_name(std::string name)
{
	_name = name;
}

void			Channel::set_users(std::map<int, User *> users)
{
	_users = users;
}

bool			Channel::set_user(User *user)
{
	std::pair<std::map<int, User *>::iterator, bool> p;

	p = _users.insert(std::make_pair(user->get_sfd(), user));
	return (p.second);
}

void			Channel::set_ID(std::string ID)
{
	_ID = ID;
}

void			Channel::set_mod(std::string mod)
{
	_mod = mod;
}

void			Channel::set_channel(std::string name)
{
	_name = name.substr(2, name.size());
}

void			Channel::set_topic(std::string topic)
{
	_topic = topic;
}

void			Channel::set_key(std::string key)
{
	_key = key;
}

void			Channel::set_limit(unsigned int limit)
{
	_limit = limit;
}

void			Channel::set_mask(std::string mask)
{
	_mask = mask;
}

// void			Channel::print(void)
// {
// 	if (!_users.empty())
// 	{
// 		for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
// 			it->second->print();
// 	}
// 	else
// 		std::cout << "users empty..." << std::endl; 
// }

void	Channel::remove_user(User *user)
{
	_users.erase(user->get_sfd());
}

void	Channel::send_to_users(std::string const &msg)
{
	std::map< int, User *>::iterator it;

	for (it = _users.begin(); it != _users.end(); it++)
	{
		std::cout << msg << std::endl;
		send(it->second->get_sfd(), msg.c_str(), msg.length(), MSG_CONFIRM);
	}
}