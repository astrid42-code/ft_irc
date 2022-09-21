# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 16:19:07 by asgaulti          #+#    #+#              #
#    Updated: 2022/09/21 11:58:00 by asgaulti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ircserv

CXX			=	c++

CXXFLAGS	=	-Wall -Wextra -Werror --std=c++98 -g3

RM			=	rm -f

SRCS		=	main.cpp									\
				Server/Server.cpp							\
				User/User.cpp								\
				Command/Cmd.cpp								\
				Command/Commands_files/ft_pass.cpp			\
				Command/Commands_files/ft_invite.cpp		\
				Command/Commands_files/ft_join_leave.cpp	\
				Command/Commands_files/ft_kick.cpp			\
				Command/Commands_files/ft_kill.cpp			\
				Command/Commands_files/ft_nick.cpp			\
				Command/Commands_files/ft_oper.cpp			\
				Command/Commands_files/ft_privmsg.cpp		\
				Command/Commands_files/ft_quit.cpp			\
				Command/Commands_files/ft_who.cpp			\
				Command/Commands_files/ft_whois.cpp			\
				Command/Commands_files/ft_list.cpp			\
				Command/Commands_files/ft_names.cpp			\
				Command/Commands_files/ft_user.cpp			\
				Command/Commands_files/ft_ping.cpp			\
				Command/Commands_files/ft_mode.cpp			\
				Channel/Channel.cpp							
#send_msg.cpp
	

INC			=	Server User Command Channel

ARGS		=	6667 pwd

OBJS_FILE	=	$(SRCS:.cpp=.o)

.c.o:
			$(CXX) $(CXXFLAGS) -I $(INC) -g -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS_FILE)
			$(CXX) $(CXXFLAGS) $(OBJS_FILE) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS_FILE)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re