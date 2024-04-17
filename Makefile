# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 14:44:36 by tmejri            #+#    #+#              #
#    Updated: 2024/04/17 02:40:34 by tmalless         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= ircserv

OBJ_PATH 	= obj/
INC_PATH 	= includes/

SRC_NAME 	+=	./srcs/Client.cpp
SRC_NAME 	+=	./srcs/ServerUtils.cpp
SRC_NAME 	+=	./srcs/main.cpp
SRC_NAME 	+=	./srcs/Parsing.cpp
SRC_NAME 	+=	./srcs/Server.cpp
SRC_NAME 	+=	./srcs/Utils.cpp
SRC_NAME 	+=	./srcs/Channel.cpp
SRC_NAME 	+=	./srcs/Message.cpp

SRC_NAME 	+=	./srcs/cmd/join.cpp
SRC_NAME 	+=	./srcs/cmd/privmsg.cpp
SRC_NAME 	+=	./srcs/cmd/topic.cpp
SRC_NAME 	+=	./srcs/cmd/kick.cpp
SRC_NAME 	+=	./srcs/cmd/mode.cpp
SRC_NAME 	+=	./srcs/cmd/invite.cpp
SRC_NAME 	+=	./srcs/cmd/quit.cpp

SRC_NAME 	+=	./srcs/cmd/nick.cpp
SRC_NAME 	+=	./srcs/cmd/user.cpp
SRC_NAME 	+=	./srcs/cmd/ping.cpp
SRC_NAME 	+=	./srcs/cmd/pass.cpp

SRC_NAME 	+=	./srcs/responses/RPL_WELCOME.cpp
SRC_NAME 	+=	./srcs/responses/RPL_YOURHOST.cpp
SRC_NAME 	+=	./srcs/responses/RPL_CREATED.cpp
SRC_NAME 	+=	./srcs/responses/RPL_MYINFO.cpp
SRC_NAME 	+=	./srcs/responses/RPL_JOIN.cpp
SRC_NAME 	+=	./srcs/responses/RPL_TOPIC.cpp
SRC_NAME 	+=	./srcs/responses/RPL_NOTOPIC.cpp
SRC_NAME 	+=	./srcs/responses/RPL_INVITE.cpp
SRC_NAME 	+=	./srcs/responses/RPL_NICK.cpp
SRC_NAME 	+=	./srcs/responses/RPL_KICK.cpp
SRC_NAME 	+=	./srcs/responses/RPL_MODE.cpp
SRC_NAME 	+=	./srcs/responses/RPL_PRIVMSG.cpp
SRC_NAME 	+=	./srcs/responses/ERR_NICKNAMEINUSE.cpp
SRC_NAME 	+=	./srcs/responses/ERR_NEEDMOREPARAMS.cpp
SRC_NAME 	+=	./srcs/responses/ERR_CHANWRONGPASS.cpp
SRC_NAME 	+=	./srcs/responses/ERR_CHANOPRIVSNEEDED.cpp
SRC_NAME 	+=	./srcs/responses/ERR_CHANNELUSERNOTINVIT.cpp
SRC_NAME 	+=	./srcs/responses/ERR_CHANNELISFULL.cpp
SRC_NAME 	+=	./srcs/responses/ERR_NOTONCHANNEL.cpp
SRC_NAME 	+=	./srcs/responses/ERR_NOSUCHCHANNEL.cpp
SRC_NAME 	+=	./srcs/responses/ERR_NOSUCHNICK.cpp
SRC_NAME 	+=	./srcs/responses/ERR_BADCHANMASK.cpp

OBJ_NAME 	= $(SRC_NAME:.cpp=.o)

SRC 		= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ 		= $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CC 			= c++
FLAGS 		= -Wall -Wextra -Werror -std=c++98 -g3

RM 			= @rm -rf

DEPS_NAME 	= $(SRC_NAME:.cpp=.d)
DEPS 		= $(addprefix $(OBJ_PATH),$(DEPS_NAME))

all: $(NAME)

$(NAME): Makefile $(OBJ)
		@echo "Build $(NAME)"
		@$(CC) $(FLAGS) -I $(INC_PATH) $(OBJ) -o $(NAME) $(LIBS) -MMD

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
		@mkdir -p $(@D)
		@$(CC) $(FLAGS) -I $(INC_PATH) -MMD -o $@ -c $<
		@echo "$< -> $@"

-include $(DEPS)

clean:
		$(RM) $(OBJ_PATH)

fclean:	clean
		$(RM) $(NAME)

re:	fclean
	@make all

#-----------------------------------------------------------------------------#

port			= 8080
password		= password

VALGRIND_PARAMS	+=	--track-fds=yes
VALGRIND_PARAMS	+=	--leak-check=full
VALGRIND_PARAMS	+=	--show-leak-kinds=all

test: re
	valgrind -q \
		${VALGRIND_PARAMS} \
		./${NAME} \
		${port} ${password}

#-----------------------------------------------------------------------------#

.PHONY: all clean fclean re