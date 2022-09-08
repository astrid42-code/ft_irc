#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include "../User/User.hpp"

class User;

class Channel
{

	public:
		Channel();
		~Channel();
		Channel & operator=(const Channel & ch_cp);
		// getters, setters
		std::string		get_name() const;
		std::string		get_ID() const;
		std::string		get_mod() const;
		std::map< std::string, User>	get_users() const;
		User 			get_user( std::string key);
		void			set_name(std::string name);
		void			set_users(std::map<  std::string, User> users);
		bool			set_user(User user);
		void			set_ID(std::string ID);
		void			set_mod(std::string mod);
		void			set_channel(std::string name);
	
	private:
		std::string				_name; // must start with '&', '#', '+' or '!' with a max of (50) char and must not contain any ' ' (spaces), G (^G or ASCII 7) or a comma (',')
		std::map< std::string, User>	_users; // une map de users avec une key en int pour l'id? et value = un objet user avec toutes les infos pour chaque)
		std::string				_ID; // depends of time ?
		std::string				_mod;
		//	MODS
		// O - give "channel creator" status;
		// o - give/take channel operator privilege;
		// v - give/take the voice privilege;
		// a - toggle the anonymous channel flag;
		// i - toggle the invite-only channel flag;
		// m - toggle the moderated channel;
		// n - toggle the no messages to channel from clients on the outside;
		// q - toggle the quiet channel flag;
		// p - toggle the private channel flag;
		// s - toggle the secret channel flag;
		// r - toggle the server reop channel flag;
		// t - toggle the topic settable by channel operator only flag;
		// k - set/remove the channel key (password);
		// l - set/remove the user limit to channel;
		// b - set/remove ban mask to keep users out;
		// e - set/remove an exception mask to override a ban mask;
		// I - set/remove an invitation mask to automatically override

		//	PRIVILEGE
		// prefix '+' for a chanel without mod and without operators
		//  INVITE  - Invite a client to an invite-only channel (mode +i)
	   	//	KICK    - Eject a client from the channel
		//	MODE    - Change the channel's mode, as well as members' privileges
		//	PRIVMSG - Sending messages to the channel (mode +n, +m, +v)
		//	TOPIC   - Change the channel topic in a mode +t channel

};


#endif