# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admaupie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 15:30:28 by admaupie          #+#    #+#              #
#    Updated: 2022/11/01 19:38:40 by admaupie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc -pthread -Wall -Werror -Wextra -g3

INCLUDES = -I../includes/

SRCS =	srcs/main.c		\
		srcs/ft_philo.c	\
		srcs/ft_time.c	\
		srcs/ft_init.c	\
		srcs/ft_utils.c	\
		srcs/ft_fork.c

OBJ = $(SRCS:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(INCLUDES) -o $(NAME) $(SRCS)

clean :
	/bin/rm -f $(OBJ)

fclean : clean
	/bin/rm -f $(NAME)

re : fclean all
