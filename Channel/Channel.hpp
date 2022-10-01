#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include "../User/User.hpp"

#define ANONYMOUS "anonymous"

class User;

class Channel
{

	public:
		Channel();
		Channel(std::string);
		~Channel();
		Channel & operator=(const Channel & ch_cp);
		bool		operator==(const Channel & ch_cp);
		// getters, setters
		std::string						get_name() const;
		std::string						get_ID() const;
		std::string						get_mod() const;
		std::map<int, User *>			get_users() const;
		User 							*get_user(int key);
		User 							*get_user(std::string nick);
		std::string						get_topic() const;
		std::string						get_key() const;
		unsigned int					get_limit() const;
		std::string						get_mask() const;

		void							set_name(std::string name);
		void							set_users(std::map<int, User *> users);
		bool							set_user(User *user);
		void							set_ID(std::string ID);
		void							set_mod(std::string mod);
		void							set_channel(std::string name);
		void							set_topic(std::string topic);
		void							set_key(std::string key);
		void							set_limit(unsigned int limit);
		void							set_mask(std::string mask);

		void							print(void);
	
		void							remove_user(User *user);

		void							send_to_users(std::string const &msg);

	private:
		std::string						_name;
		std::map< int, User *>			_users;
		std::string						_ID;
		std::string						_mod;
		std::string						_topic;
		std::string						_key;
		std::string						_mask;
		unsigned int					_limit;

};


#endif

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
		//	prefix '+' for a chanel without mod and without operators
		//  INVITE  - Invite a client to an invite-only channel (mode +i)
	   	//	KICK    - Eject a client from the channel
		//	MODE    - Change the channel's mode, as well as members' privileges
		//	PRIVMSG - Sending messages to the channel (mode +n, +m, +v)
		//	TOPIC   - Change the channel topic in a mode +t channel