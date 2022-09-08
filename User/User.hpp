#ifndef USER_HPP
#define USER_HPP

#include <iostream>
// #include "Server/Server.hpp"
#include "../Command/Cmd.hpp"

#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


class User
{
	public:
		User();
		~User();
		User & operator=(const User & user_cp);
		// getters, setters
		std::string 	get_user() const;
		std::string		get_name() const;
		std::string 	get_nick() const;
		std::string 	get_pwd() const;
		std::string		get_mod() const; // only fill with 'aiwroOs'
		int				get_operator() const; // 0 for no access 1 for operator
		void			set_user(std::string user);
		void			set_name(std::string name);
		void			set_nick(std::string nick);
		void			set_pwd(std::string pwd);
		void			set_mod(std::string mod);
		void			set_operator(int op);
		bool			check_nick(std::string new_nick);
		bool			find_mod(std::string mod);
		void			print(void) const;

	private:
		std::string				_user;
		std::string				_name;
		std::string				_nick;
		std::string				_pwd;
		std::string				_mod;
		int						_operator;
};

#endif