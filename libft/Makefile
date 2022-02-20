
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 17:43:09 by pmontese          #+#    #+#              #
#    Updated: 2019/11/26 15:51:28 by pmontese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY = all clean

CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a

SRC = $(wildcard *.c)

INCLUDE = libft.h

OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $@ $^
	ranlib $(NAME)

%.o:%.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all