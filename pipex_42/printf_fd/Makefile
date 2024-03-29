# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 08:55:01 by bboissen          #+#    #+#              #
#    Updated: 2024/02/07 14:01:15 by bboissen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	../lib/libftprintf.a
CC 		=	cc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	printf_fd.c			\
			converter.c			\
			ft_putnbr_base.c	\
			ft_strchr.c			\
			seq_write.c 		\
			ft_strlen.c
			

OBJS	=	$(SRCS:.c=.o)
HEADERS	=	printf_fd.h

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $(OBJS)


%.o: %.c $(HEADERS) Makefile
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re