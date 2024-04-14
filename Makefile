# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 14:44:36 by tmejri            #+#    #+#              #
#    Updated: 2024/04/14 19:23:43 by tmejri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= ircserv

OBJ_PATH 	= obj/
INC_PATH 	= includes/

SRC_NAME 	+=	./srcs/Client.cpp
SRC_NAME 	+=	./srcs/ServerCommands.cpp
SRC_NAME 	+=	./srcs/main.cpp
SRC_NAME 	+=	./srcs/Nick.cpp
SRC_NAME 	+=	./srcs/Parsing.cpp
SRC_NAME 	+=	./srcs/Server.cpp
SRC_NAME 	+=	./srcs/Utils.cpp
SRC_NAME 	+=	./srcs/Transmission.cpp
SRC_NAME 	+=	./srcs/Channel.cpp
SRC_NAME 	+=	./srcs/Message.cpp
SRC_NAME 	+=	./srcs/cmd/join.cpp
SRC_NAME 	+=	./srcs/cmd/privmsg.cpp
SRC_NAME 	+=	./srcs/cmd/kick.cpp
SRC_NAME 	+=	./srcs/errors.cpp
SRC_NAME 	+=	./srcs/cmd/mode.cpp
SRC_NAME 	+=	./srcs/cmd/invite.cpp

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
		mkdir -p $(@D)
		$(CC) $(FLAGS) -I $(INC_PATH) -MMD -o $@ -c $<

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