# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 13:59:53 by gdumas            #+#    #+#              #
#    Updated: 2024/04/12 12:40:51 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME		=	minishell
CC			=	gcc
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

BUILTINS	=	cd			\
				echo		\
				env			\
				exit		\
				exp_handler	\
				exp_print	\
				pwd			\
				unset

ENV			=	env			\
				get_env		\
				init		\
				sort_env	\
				shlvl

EXEC		=	bin		\
				builtin	\
				exec	\
				pipe

MAIN		=	minishell	\
				redir		\
				signal

PARSING		=	expansions	\
				line		\
				tokens

UTILS		=	expansions	\
				fd			\
				free		\
				parsing		\
				token		\
				type		\
				update_tokens

SRCS		=	$(addprefix $(SRC_DIR)builtins/, $(addsuffix .c, $(BUILTINS)))	\
				$(addprefix $(SRC_DIR)env/, $(addsuffix .c, $(ENV)))			\
				$(addprefix $(SRC_DIR)exec/, $(addsuffix .c, $(EXEC)))		\
				$(addprefix $(SRC_DIR)main/, $(addsuffix .c, $(MAIN)))			\
				$(addprefix $(SRC_DIR)parsing/, $(addsuffix .c, $(PARSING)))	\
				$(addprefix $(SRC_DIR)utils/, $(addsuffix .c, $(UTILS)))

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