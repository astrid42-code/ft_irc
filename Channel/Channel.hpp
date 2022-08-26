#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>

namespace irc{

	class User;

	class Channel{

		public:
			Channel();
			~Channel();

			Channel & operator=(const Channel & ch_cp);

			// getters, setters
			std::string		get_channel() const;
			void			set_channel(std::string name);

		private:
			std::map< int, User *>	_users; // une map de users avec une key en int pour l'id? et value = un objet user avec toutes les infos pour chaque)

	};
}


#endif