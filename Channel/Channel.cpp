#include "Channel.hpp"

Channel::Channel()
{}

Channel::~Channel()
{}

Channel & Channel::operator=(const Channel & ch_cp)
{
	this->_name = ch_cp._name;
	return (*this);
}

std::string				Channel::get_name() const
{
	return (_name);
}

std::string				Channel::get_ID() const
{
	return (_ID);
}

std::string				Channel::get_mod() const
{
	return (_mod);
}

std::map< int, User *>	Channel::get_user() const
{
	return (_users);
}