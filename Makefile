# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/08 16:51:41 by adu-pelo          #+#    #+#              #
#    Updated: 2016/03/18 10:36:30 by adu-pelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

C_DIR = sources
C_DIRS = $(shell find $(C_DIR) -type d -follow -print)
C_FILES = $(shell find $(C_DIRS) -type f -follow -print | grep -w "[.c]$$")

O_DIR = .tmp/obj
O_DIRS = $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES = $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

FLAGS = -Wall -Werror -Wextra
INCLUDES = -Iincludes -Ilibft
LIB = -L./libft -lft

all: $(NAME)

$(NAME): $(O_FILES)
	make -C ./libft
	gcc $(FLAGS) $^ $(LIB) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	mkdir -p $(O_DIRS) $(O_DIR)
	gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:	
	rm -rf $(O_FILES)
	make clean -C libft

fclean: clean
	@make fclean -C libft
	@rm $(NAME) || true
	@rm -rf .tmp/

re: fclean all

.PHONY : all clean fclean re
