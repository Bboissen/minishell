# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 13:27:07 by gdumas            #+#    #+#              #
#    Updated: 2024/05/02 09:31:23 by talibabtou       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME	=	libft.a
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror -I $(INCS)
SRC_DIR	=	src/
OBJ_DIR	=	obj/
INCS	=	includes/
HEADER	=	$(addprefix $(INCS), libft.h)

AR		=	ar rcs


# Sources & Objects #

GNL_SRC =	get_next_line

IS_SRC =	ft_isalnum		\
			ft_isalpha		\
			ft_isascii		\
			ft_iscount		\
			ft_isdigit		\
			ft_ishexdigit	\
			ft_isin			\
			ft_isprint		\
			ft_isspace		\
			ft_isspacenl	\
			ft_iswhere

LST_SRC =	ft_lstadd_back	\
			ft_lstadd_front	\
			ft_lstclear		\
			ft_lstdelone	\
			ft_lstiter		\
			ft_lstlast		\
			ft_lstmap		\
			ft_lstnew		\
			ft_lstsize

MATH_SRC = 	ft_abs		\
			ft_baselen	\
			ft_hexlen	\
			ft_nbrlen	\
			ft_power

MEM_SRC =	ft_bzero	\
			ft_calloc	\
			ft_memccpy	\
			ft_memchr	\
			ft_memcmp	\
			ft_memcpy	\
			ft_memdel	\
			ft_memmove	\
			ft_memset	\
			ft_realloc

PFD_SRC	=	converter		\
			printf_fd

PUT_SRC =	ft_putchar_fd	\
			ft_putchar		\
			ft_putendl_fd	\
			ft_putendl		\
			ft_putnbr_base	\
			ft_putnbr_fd	\
			ft_putnbr		\
			ft_putstr_fd	\
			ft_putstr

SKIP_SRC =	ft_skip_char	\
			ft_skip_chars	\
			ft_skip_space	\
			ft_skip_spacenl

STR_SRC =	ft_split	\
			ft_strcat	\
			ft_strchr	\
			ft_strcmp	\
			ft_strcpy	\
			ft_strdup	\
			ft_strequ	\
			ft_strisnum	\
			ft_striteri	\
			ft_strjoin	\
			ft_strlcat	\
			ft_strlcpy	\
			ft_strlen	\
			ft_strmapi	\
			ft_strncmp	\
			ft_strndup	\
			ft_strnstr	\
			ft_strrchr	\
			ft_strtok	\
			ft_strtrim	\
			ft_substr

TO_SRC =	ft_atoi		\
			ft_itoa		\
			ft_tolower	\
			ft_toupper

SRCS	=	$(addprefix $(SRC_DIR)ft_gnl/, $(addsuffix .c, $(GNL_SRC)))		\
			$(addprefix $(SRC_DIR)ft_is/, $(addsuffix .c, $(IS_SRC)))		\
			$(addprefix $(SRC_DIR)ft_lst/, $(addsuffix .c, $(LST_SRC)))		\
			$(addprefix $(SRC_DIR)ft_math/, $(addsuffix .c, $(MATH_SRC)))	\
			$(addprefix $(SRC_DIR)ft_mem/, $(addsuffix .c, $(MEM_SRC)))		\
			$(addprefix $(SRC_DIR)ft_printfd/, $(addsuffix .c, $(PFD_SRC)))	\
			$(addprefix $(SRC_DIR)ft_put/, $(addsuffix .c, $(PUT_SRC)))		\
			$(addprefix $(SRC_DIR)ft_skip/, $(addsuffix .c, $(SKIP_SRC)))	\
			$(addprefix $(SRC_DIR)ft_str/, $(addsuffix .c, $(STR_SRC)))		\
			$(addprefix $(SRC_DIR)ft_to/, $(addsuffix .c, $(TO_SRC)))

OBJS	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))


# Rules #

all				:	$(NAME)

$(NAME)			:	$(OBJS)
				@echo "\nCreating libft.a"
				@$(AR) $(NAME) $^
				@echo "Done !"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER)| $(OBJ_DIR)
				@mkdir -p $(dir $@)
				@printf "Generating libft objects... %-33.33s\r" $@
				@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)		:
				@mkdir -p $(OBJ_DIR)

clean			:
				@if [ -d "$(OBJ_DIR)" ]; then			\
					echo "Cleaning libft obj/ directory";	\
					rm -rf $(OBJ_DIR);					\
				fi

fclean			:	clean
				@if [ -f "libft.a" ]; then				\
					echo "Cleaning libft.a";		\
					rm -f $(NAME);						\
				fi

re				:	fclean all


.PHONY			:	all clean fclean re
