#ifndef USER_HPP
#define USER_HPP

#include <iostream>
// #include "Server/Server.hpp"
#include "../Command/Cmd.hpp"
#include "../Channel/Channel.hpp"

#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()


class Channel;

class User
{
	public:
		User();
		User(std::string prenom, std::string nom, std::string nickname);
		User(std::string nickname, int sdf);
		User(int sdf);
		~User();

		User			&operator=(const User & user_cp);
		bool			operator==(const User & user_cp);

		std::string 			get_user() const;
		std::string				get_name() const;
		std::string 			get_nick() const;
		std::string				get_host() const;
		int						get_sfd() const;
		std::string				get_mod() const; // only fill with 'aiwroOs'
		int						get_valid() const; // 0 for no access 1 for operator
		std::string				get_hostname() const;
		Channel					*get_channel(std::string name);
		std::string				get_channel_name();
		std::vector<Channel *>	*get_chans() const;
		std::string				get_away() const;

		void			set_user(std::string user);
		void			set_name(std::string name);
		void			set_nick(std::string nick);
		void			set_host(std::string host);
		void			set_mod(std::string mod);
		void			set_valid(int op);
		void			set_sfd(int sfd);
		void			set_chan(Channel *chan);
		void			set_away(std::string msg);

		bool			check_nick(std::string new_nick);
		bool			find_mod(std::string mod);
		void			print(void) const;

		std::vector<Channel *>::iterator	it_chan(std::string chan_name);

		void			remove_chan(Channel * channel);

		friend std::ostream	&operator<<(std::ostream &os, const User &user_cp);

	private:
		std::string				_user;
		std::string				_name;
		std::string				_nick;
		std::string				_mod;
		std::string				_host;
		int						_sfd;
		int						_valid;
		std::string				_away;
		std::vector<Channel *>	*_vchan;
};

#endif