# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amema <amema@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 16:17:16 by amema             #+#    #+#              #
#    Updated: 2024/03/04 20:53:21 by amema            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

CFLAGS		:= -Wall -Werror -Wextra -pthread -g #-fsanitize=thread

SRCS		:= 	control.c main.c init.c input.c routine.c time.c utils.c \

OBJS		:= ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@make clean

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
