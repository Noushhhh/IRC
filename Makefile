NAME = 			irc_serv

#PARSING_FILES = 	

SRC_FILES = main.cpp \

SRC = 			${addprefix src/, ${SRC_FILES}} \
			#	${addprefix parsing/, ${PARSING_FILES}} \

OBJS =			${SRC:.cpp=.o}

#INCLUDES			= 	irc.hpp \

CMD = 			c++
FLAGS = 		-Wall -Werror -Wextra -std=c++98 #-MD
DEP = 			${OBJS:.o=.d}

all: 			library $(NAME)

$(NAME): 		$(OBJS) $(INCLUDES) Makefile
				$(CMD) $(FLAGS) $(OBJS) -o $(NAME)
				
%.o: 			%.cpp $(INCLUDES)
				$(CMD) $(FLAGS) -c $< -o $@

clean:
		rm -rf $(OBJS) ${OBJS:.o=.d}

fclean: clean
		rm -rf $(NAME)
		
re: fclean all

.PHONY: library clean all re fclean

#-include $(DEP)
