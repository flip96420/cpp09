# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 18:07:40 by phillymilly       #+#    #+#              #
#    Updated: 2026/01/03 18:08:20 by phillymilly      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -g -std=c++98
RM = rm -rf

CPP_09 = PmergeMe

CPP_09_SRC =	./main.cpp		\
				./PmergeMe.cpp	\

CPP_09_OBJ = $(CPP_09_SRC:.cpp=.o)

all: $(CPP_09)

$(CPP_09): $(CPP_09_OBJ) $(LIBFT)
	$(CPP) $(CPPFLAGS) $(CPP_09_OBJ) $(LIBFT) -o PmergeMe

clean:
	$(RM) $(CPP_09_OBJ)
fclean: clean
	$(RM) $(CPP_09)
re: fclean all

.PHONY : all clean fclean re