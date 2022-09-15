#ifndef USER_HPP
#define USER_HPP

#include <iostream>
// #include "Server/Server.hpp"
#include "../Command/Cmd.hpp"
#include "../Channel/Channel.hpp"

#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


class Channel;
class User
{
	public:
		User();
		~User();

		User			&operator=(const User & user_cp);
		bool			operator==(const User & user_cp);

		std::string 	get_user() const;
		std::string		get_name() const;
		std::string 	get_nick() const;
		std::string		get_host() const;
		int				get_sfd() const;
		std::string 	get_pwd() const;
		std::string		get_mod() const; // only fill with 'aiwroOs'
		int				get_operator() const; // 0 for no access 1 for operator

		void			set_user(std::string user);
		void			set_name(std::string name);
		void			set_nick(std::string nick);
		void			set_host(std::string host);
		void			set_pwd(std::string pwd);
		void			set_mod(std::string mod);
		void			set_operator(int op);
		void			set_sfd(int sfd);
		void			set_chan(Channel &chan);
		// void			set_chan(Channel *chan);

		bool			check_nick(std::string new_nick);
		bool			find_mod(std::string mod);
		void			print(void) const;

		bool			isOnChan(std::string &chan_name);

		friend std::ostream	&operator<<(std::ostream &os, const User &user_cp);

	private:
		std::string				_user;
		std::string				_name;
		std::string				_nick;
		std::string				_pwd;
		std::string				_mod;
		std::string				_host;
		int						_sfd;
		int						_operator;
		std::vector<Channel *>	_vchan; // liste des channels dans lesquels le user est connecte (quand il join)
};

// std::ostream		&operator<<(std::ostream os, const User &user_cp);

#endif

// associer le user a la map de channels auxquels il est connecte (ici ou dans le server?)