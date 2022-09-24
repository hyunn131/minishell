# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 16:14:31 by docho             #+#    #+#              #
#    Updated: 2022/09/24 19:06:09 by junhkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = -lft -L./libft
RFLAGS = -lreadline -L/Users/docho/.brew/opt/readline/lib -I/Users/docho/.brew/opt/readline/include -lft -L./libft
SRCS = cmd.c process.c builtin.c error.c io.c \
	split.c utils.c ft_calloc.c ft_putstr_fd.c \
	quotes.c dollar.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(LIB) $(RFLAGS) -o $(NAME) $(OBJS)

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re:
	make fclean
	make all
