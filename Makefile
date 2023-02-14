NAME = 			irc_serv

#PARSING_FILES = 	

SRC_FILES = main.cpp \
			Server.cpp	\
			Message.cpp	\
			Channel.cpp	\
			User.cpp	

SRC = 			${addprefix src/, ${SRC_FILES}} \

OBJS =			${SRC:.cpp=.o}

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
