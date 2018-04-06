# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/07 19:00:43 by mbriffau          #+#    #+#              #
#    Updated: 2017/10/17 16:58:21 by mbriffau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = mbriffau.filler

FLAGS = -Wall -Werror -Wextra
INC = -I ./incl/

### PATH ###
SRCS_PATH = srcs/
OBJ_PATH  = obj/
LIBFT_PATH = libft/

SRCS_NAME =	main.c \
			parse.c \
			valid_positions.c \
			solve.c \
			break_through.c \
			reach_borders.c \
			check_min.c \
			scoring1.c \
			scoring2.c \
			get_picture.c \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

### COMPILE ###
all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@gcc $(FLAGS) $(OBJ) $(INC) -L $(LIBFT_PATH) libft/libftprintf.a -o $(NAME)
	@echo "$(NAME)\033[1;0m\033[32m created.\033[0m"
	
$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
		@echo "$(notdir $<)\033[1m\033[32m compiled.\033[0m"
		@mkdir -p `dirname $@`
		@gcc -c $(FLAGS) $(INC) $< -o $@

clean:
		@make -C $(LIBFT_PATH) fclean
		@/bin/rm -rf $(OBJ_PATH)
		@/bin/rm -rf filler.trace
		@/bin/rm -rf board.map
		@echo "$(NAME) \033[1;0m\033[31mobjects files removed.\033[0m"

fclean: clean
		@/bin/rm -rf $(NAME)
		@echo "$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
