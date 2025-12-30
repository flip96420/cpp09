# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/30 14:31:03 by phillymilly       #+#    #+#              #
#    Updated: 2025/12/30 17:58:17 by phillymilly      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -g -std=c++98
RM = rm -rf

CPP_09 = RPN

CPP_09_SRC =	./main.cpp				\
				./RPN.cpp				\

CPP_09_OBJ = $(CPP_09_SRC:.cpp=.o)

all: $(CPP_09)

$(CPP_09): $(CPP_09_OBJ) $(LIBFT)
	$(CPP) $(CPPFLAGS) $(CPP_09_OBJ) $(LIBFT) -o RPN

clean:
	$(RM) $(CPP_09_OBJ)
fclean: clean
	$(RM) $(CPP_09)
re: fclean all

.PHONY : all clean fclean re