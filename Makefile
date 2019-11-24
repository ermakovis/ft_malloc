# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcase <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 11:31:10 by tcase             #+#    #+#              #
#    Updated: 2019/11/12 20:41:21 by tcase            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=malloc

CC=gcc
FLAGS=-g# -Wall -Werror -Wextra

SRC_DIR=./src
LIB_DIR=./libft
OBJ_DIR=./obj

SRC_NAME=main.c\
		malloc.c\
		free.c\
		realloc.c\
		calloc.c\
		show_alloc.c\
		ft_malloc_misc.c

SRC = $(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))
OBJ = $(SRC)
INC = -I ./includes -I $(LIB_DIR)/includes

all: $(NAME)

$(NAME) : $(OBJ)
	@make -s -C $(LIB_DIR)
	@$(CC) -shared -fPIC $(OBJ) $(LIB_DIR)/libft.a $(INC) -o $(NAME).so

test : $(OBJ)
	@make -s -C $(LIB_DIR)
	@$(CC) -o $(NAME) $(SRC) $(LIB_DIR)/libft.a $(INC) $(FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p obj
	@$(CC) -o $@ -c $< $(INC) $(FLAGS)
	@echo "\033[0m\033[36m$(notdir $<)\033[1m\033[34m OK\033[0m"

clean:
		@make clean -s -C $(LIB_DIR)
		@rm -f $(OBJ)

fclean: clean
		@make fclean -s -C $(LIB_DIR)
		@find . -type f -name ".*.swp" -exec rm -f {} \;
		@rm -rf *test*
		@rm -rf $(NAME)*

re:	fclean all

.PHONY: all, clean, fclean, re
