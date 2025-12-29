# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 15:16:08 by pschmunk          #+#    #+#              #
#    Updated: 2025/12/29 23:12:53 by phillymilly      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -g -std=c++98
RM = rm -rf

CPP_09 = btc

CPP_09_SRC =	./main.cpp				\
				./BitcoinExchange.cpp	\

CPP_09_OBJ = $(CPP_09_SRC:.cpp=.o)

all: $(CPP_09)

$(CPP_09): $(CPP_09_OBJ) $(LIBFT)
	$(CPP) $(CPPFLAGS) $(CPP_09_OBJ) $(LIBFT) -o btc

clean:
	$(RM) $(CPP_09_OBJ)
fclean: clean
	$(RM) $(CPP_09)
re: fclean all

.PHONY : all clean fclean re