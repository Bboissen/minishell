# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 10:34:27 by bboissen          #+#    #+#              #
#    Updated: 2024/02/07 14:02:14 by bboissen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	../lib/libft.a
CC 		=	cc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	ft_atoi.c		\
			ft_bzero.c		\
			ft_calloc.c		\
			ft_isalnum.c	\
			ft_isalpha.c	\
			ft_isascii.c	\
			ft_isdigit.c	\
			ft_isprint.c	\
			ft_itoa.c		\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_memcpy.c		\
			ft_memmove.c	\
			ft_memset.c		\
			ft_putchar_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\
			ft_putstr_fd.c	\
			ft_split.c		\
			ft_strchr.c		\
			ft_strdup.c		\
			ft_striteri.c	\
			ft_strjoin.c	\
			ft_strlcat.c	\
			ft_strlcpy.c	\
			ft_strlen.c		\
			ft_strmapi.c	\
			ft_strncmp.c	\
			ft_strnstr.c	\
			ft_strrchr.c	\
			ft_strtrim.c	\
			ft_substr.c		\
			ft_tolower.c	\
			ft_toupper.c	\
			ft_lstadd_back.c	\
			ft_lstadd_front.c	\
			ft_lstiter.c		\
			ft_lstlast.c		\
			ft_lstnew.c			\
			ft_lstsize.c

OBJECTS	=	$(SRCS:.c=.o)
OBJECTS_B	=	$(SRCS_B:.c=.o)
HEADERS	=	libft.h

ifdef WITH
	OBJS = $(OBJECTS_B) $(OBJECTS)
else
	OBJS = $(OBJECTS)
endif

all: $(NAME)
		
$(NAME): $(OBJS)
	ar -rcs $@ $(OBJS)

bonus: $(NAME)
	make WITH=1 all

%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OBJECTS_B)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
