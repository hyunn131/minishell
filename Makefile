# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 16:14:31 by docho             #+#    #+#              #
#    Updated: 2022/10/03 12:05:50 by junhkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = -lft -L./libft
RFLAGS = -lreadline -L/Users/junhkim/.brew/opt/readline/lib
IFLAGS = -I/Users/junhkim/.brew/opt/readline/include
SRCS = cmd.c process.c builtin.c error.c io.c cmd2.c \
	utils.c ft_putstr_fd.c quotes.c dollar.c main.c \
	builtin_cd.c builtin_echo.c builtin_env_pwd.c builtin_exit.c \
	builtin_export1.c builtin_export2.c builtin_unset.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(LIB) $(RFLAGS) -o $(NAME) $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re:
	make fclean
	make all
