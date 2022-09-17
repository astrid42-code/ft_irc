#include "Channel.hpp"

Channel::Channel() : _name("NoName"), _ID("toto"), _mod("")
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

std::string		Channel::get_topic() const{
	return (_topic);
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

std::cout << "COUCOU SET USER DANS CHAN" << std::endl;
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
	_name = name;
}

void			Channel::set_topic(std::string topic){
	_topic = topic;
}

void			Channel::print(void)
{
	std::map<int, User *>::iterator it = _users.begin();

	std::cout << "name:" + _name << std::endl;
	while (it != _users.end())
	{
		it->second->print();
		it++;
	}
}

void	Channel::remove_user(User *user){
	// (void)user;
	std::map<int, User *>::iterator it;

	std::cout << "remove_user sfd = " << user->get_sfd() << std::endl;
	
	// for (it = _users.begin(); it != _users.end(); it++){
	// 	std::cout << it->second << std::endl;
	// }

	it = _users.find(user->get_sfd()); // lui envoyer la cle de la map de user (mai ou est-elle definie et recuperable?)
	std::cout << "remove_user it = " << it->second << std::endl;
	if (it != _users.end()){
		delete it->second;
		_users.erase(user->get_sfd()); // erase la key
	}
}



// pb : le get_sfd n'est pas bon = ne recupere pas le numero au set??