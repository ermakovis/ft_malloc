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


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=libft_malloc_$(HOSTTYPE).so
LIB_NAME 	=libft_malloc.so

CC=			gcc
FLAGS=		-fPIC #-Wall -Werror -Wextra
LIB_FLAGS=	-shared

SRC_DIR=	./src
UTILS_DIR=	./src/utils
OBJ_DIR=	./obj

SRC_NAME= 	malloc.c\
			free.c\
			realloc.c\
			calloc.c\
			find_block.c\
			find_zone.c\
			malloc_log.c\
			malloc_misc.c
			#show_alloc.c

UTILS_NAME=	ft_strlen.c\
			ft_strchrlen.c\
			ft_strcmp.c\
			ft_putstr.c\
			ft_bzero.c

SRC= 		$(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))
UTILS=		$(addprefix $(OBJ_DIR)/, $(UTILS_NAME:.c=.o))
OBJ=		$(SRC) $(UTILS)
INC =		-I ./includes

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(LIB_FLAGS) $(OBJ) -o $(NAME)
	@rm -f $(LIB_NAME)
	@ln -s $(NAME) $(LIB_NAME)
	@printf "\033[0m\033[35m%-40s\033[1m\033[34m%s\033[0m\n" "Compilation" "Done"

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(FLAGS) -O0 -g $(INC) 
	@printf "\033[0m\033[36m%-40s\033[1m\033[34m%s\033[0m\n" "$(notdir $<)" "Done"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(FLAGS) -O0 -g $(INC) 
	@printf "\033[0m\033[36m%-40s\033[1m\033[34m%s\033[0m\n" "$(notdir $<)" "Done"

clean:
	@rm -f $(OBJ)
	@printf "\033[0m\033[33m%-40s\033[1m\033[34m%s\033[0m\n" "Clean" "Done"

fclean: clean
	@rm -rf $(NAME) $(LIB_NAME)
	@printf "\033[0m\033[33m%-40s\033[1m\033[34m%s\033[0m\n" "Full Clean" "Done"

re:	fclean all

.PHONY: all, clean, fclean, re
