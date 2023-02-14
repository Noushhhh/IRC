NAME = 			irc_serv

#PARSING_FILES = 	

SRC_FILES = main.cpp \
			Server.cpp	\
			Message.cpp	\
			Channel.cpp	\
			User.cpp	

CMD_FILES = pass.cpp \
			nick.cpp \
			cmdUser.cpp \
			quit.cpp \
			join.cpp \
			part.cpp \
			mode.cpp \
			topic.cpp \
			names.cpp \
			list.cpp \
			invite.cpp \
			kick.cpp \
			msg.cpp \
			privmsg.cpp \
			notice.cpp \
			ping_pong.cpp

SRC = 		${addprefix src/, ${SRC_FILES}}
SRC_CMD =	${addprefix src/cmds/, ${CMD_FILES}} 

OBJS =			${SRC:.cpp=.o} ${SRC_CMD:.cpp=.o}

INCLUDES			= 	includes/irc.hpp 		\
						includes/Server.hpp	\
						includes/Message.hpp	\
						includes/Channel.hpp	\
						includes/Replies.hpp	\
						includes/User.hpp

CMD = 			c++
FLAGS = 		-Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3 #-MD
DEP = 			${OBJS:.o=.d}

all: 			library $(NAME)

$(NAME): 		$(OBJS) $(INCLUDES) 
				$(CMD) $(FLAGS) $(OBJS) -o $(NAME)
				
%.o: 			%.cpp $(INCLUDES) Makefile
				$(CMD) $(FLAGS) -c $< -o $@

clean:
		rm -rf $(OBJS) ${OBJS:.o=.d}

fclean: clean
		rm -rf $(NAME)
		
re: fclean all

.PHONY: library clean all re fclean

#-include $(DEP)
