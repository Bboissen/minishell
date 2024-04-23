# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 13:59:53 by gdumas            #+#    #+#              #
#    Updated: 2024/04/23 15:12:09 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME		=	minishell
CC			=	cc
FLAGS		=	-Werror -Wall -Wextra $(IFLAGS)
IFLAGS		=	-I $(INCS) -I $(LIBFT_DIR)includes/
LFLAGS		=	-L libft -lft -lreadline

INCS		=	inc/
HEADER		=	$(addprefix $(INCS), minishell.h)
LIBFT_H		=	$(addprefix $(LIBFT_DIR)includes/, libft.h)

SRC_DIR		=	src/
OBJ_DIR		=	obj/
LIBFT_DIR	=	libft/


# Sources & Objects #

BUILTINS	=	exit #cd		\
				echo		\
				env			\
				exit		\
				export		\
				pwd			\
				unset#

ENV			=	env			\
				init		\
				shlvl		\
				sort_env

ERROR		=	error_manager	\
				lexer_err

EXEC		=	pipe

LEXER		=	lexer		\
				lex_utils	\
				heredoc

PARSER		=	expansions	\
				parser		\
				parser_utils

UTILS		=	fd			\
				free		\
				signal

MAIN		=	minishell

SRCS		=	$(addprefix $(SRC_DIR)builtins/, $(addsuffix .c, $(BUILTINS)))	\
				$(addprefix $(SRC_DIR)env/, $(addsuffix .c, $(ENV)))			\
				$(addprefix $(SRC_DIR)error/, $(addsuffix .c, $(ERROR)))		\
				$(addprefix $(SRC_DIR)exec/, $(addsuffix .c, $(EXEC)))			\
				$(addprefix $(SRC_DIR)lexer/, $(addsuffix .c, $(LEXER)))		\
				$(addprefix $(SRC_DIR)parser/, $(addsuffix .c, $(PARSER)))		\
				$(addprefix $(SRC_DIR)utils/, $(addsuffix .c, $(UTILS)))		\
				$(addprefix $(SRC_DIR), $(addsuffix .c, $(MAIN)))

OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))


# Rules #

.DEFAULT_GOAL	:=	all

all				:	force $(NAME)

$(NAME)			:	$(OBJS)
				@echo "\nCompiling minishell"
				@$(CC) $(OBJ) $(FLAGS) -o $@ $(OBJS) $(LFLAGS)
				@echo "Done !"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER) $(LIBFT_H) Makefile | $(OBJ_DIR)
				@mkdir -p $(dir $@)
				@printf "Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)		:
				@mkdir -p $(OBJ_DIR)

force			:
				@make -sC libft
				@if [ ! -f "libft/libft.a" ]; then	\
					echo "Making libft.a";			\
					make -sC libft;					\
				fi


clean			:
				@if [ -d "$(OBJ_DIR)" ]; then				\
					echo "Cleaning minishell obj/ directory";	\
					rm -rf $(OBJ_DIR);						\
				fi
				@make -sC libft clean

fclean			:	clean
				@if [ -f "minishell" ]; then			\
					echo "Cleaning program: minishell";	\
					rm -f $(NAME);						\
				fi
				@make -sC libft fclean


re				:	fclean all

.PHONY			:	all re clean fclean force
