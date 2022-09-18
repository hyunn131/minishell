# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: docho <docho@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 16:14:31 by docho             #+#    #+#              #
#    Updated: 2022/09/19 06:01:41 by docho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RFLAGS = -lreadline -L/Users/docho/.brew/opt/readline/lib -I/Users/docho/.brew/opt/readline/include
SRCS = cmd.c process.c builtin.c error.c io.c split.c utils.c ft_calloc.c ft_putstr_fd.c quotes.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(RFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all
