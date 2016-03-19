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

SRC = b_cd.c b_env.c b_setenv.c b_unsetenv.c builtin.c exe_cmd.c main.c \
	  prompt.c tools.c tools2.c

OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean $(NAME)

.PHONY : all clean fclean re
