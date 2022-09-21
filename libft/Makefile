# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 12:50:55 by junhkim           #+#    #+#              #
#    Updated: 2022/08/30 06:34:42 by junhkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
RM = rm -f
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	   ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	   ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	   ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	   ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	   ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	   ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	   ft_putnbr_fd.c ft_atoi.c

SRCS_b = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		 ft_lstmap.c

OBJS = $(SRCS:.c=.o)

OBJS_b = $(SRCS_b:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJS)
	$(AR) $@ $^

all: $(NAME)

bonus: $(OBJS_b)
	make all
	$(AR) $(NAME) $(OBJS_b)

clean:
	$(RM) $(OBJS) $(OBJS_b)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
