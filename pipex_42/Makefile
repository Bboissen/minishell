# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 11:08:39 by bboissen          #+#    #+#              #
#    Updated: 2024/02/07 13:33:26 by bboissen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR 	=	./src
SRC_B_DIR 	=	./src_bonus
OBJ_DIR		=	./obj
OBJ_B_DIR	=	./obj_bonus
HDR_DIR		=	./includes
HDR_B_DIR	=	./includes_bonus
LIB_DIR		=	./lib
MAKEFILE	=	./Makefile

NAME	=	pipex
CC 		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	$(SRC_DIR)/main.c		\
			$(SRC_DIR)/pipe.c		\
			$(SRC_DIR)/list.c		\
			$(SRC_DIR)/error.c		\
			$(SRC_DIR)/parser.c		\
			$(SRC_DIR)/filler.c		\
			$(SRC_DIR)/path.c
			
SRCS_B	=	$(SRC_B_DIR)/main_bonus.c		\
			$(SRC_B_DIR)/pipe_bonus.c		\
			$(SRC_B_DIR)/list_bonus.c		\
			$(SRC_B_DIR)/error_bonus.c		\
			$(SRC_B_DIR)/parser_bonus.c		\
			$(SRC_B_DIR)/filler_bonus.c		\
			$(SRC_B_DIR)/path_bonus.c
				
OBJECTS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJECTS_B  = $(SRCS_B:$(SRC_B_DIR)/%.c=$(OBJ_B_DIR)/%.o)

HEADERS		=	$(HDR_DIR)/utils.h
HEADERS_B	=	$(HDR_B_DIR)/utils_bonus.h

LDFLAGS = -L $(LIB_DIR)

ifdef WITH_BONUS
	OBJS = $(OBJECTS_B)
	HEAD = $(HEADERS_B)
	OBJ_DIR = $(OBJ_B_DIR)
	SRC_DIR = $(SRC_B_DIR)
else
	OBJS = $(OBJECTS)
	HEAD = $(HEADERS)
endif

all: 
	mkdir -p $(LIB_DIR)
	mkdir -p $(OBJ_DIR)
	$(MAKE) -C ./libft
	$(MAKE) -C ./printf_fd
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(addprefix -l, ft ftprintf)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD) $(MAKEFILE) | $(OBJ_DIR)
	$(CC) -c $< -o $@

bonus:
	make WITH_BONUS=1 all

clean:
	rm -rf $(OBJ_B_DIR) $(OBJ_DIR) $(LIB_DIR)

fclean: clean
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./printf_fd fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
