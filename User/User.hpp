#ifndef USER_HPP
#define USER_HPP

#include <iostream>
// #include "Server/Server.hpp"

namespace irc{

	class User{

		public:
			User();
			~User();

			User & operator=(const User & user_cp);

			// getters, setters
			std::string 	get_user() const;
			std::string 	get_pwd() const;
			void			set_user(std::string name);
			void			set_pwd(std::string pwd);

			bool	check_user();


		private:
			std::string _name;
			std::string _pwd;
	};
}

#endif