# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgras <mgras@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/26 15:24:20 by mgras             #+#    #+#              #
#    Updated: 2015/03/25 17:11:05 by mgras            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/

SRC_NAME =	ft_builtin_env.c \
			ft_0_free.c \
			ft_builtin_utility.c \
			ft_env.c \
			ft_core.c \
			ft_get_next_line.c \
			ft_builtin_fnc.c \
			ft_error.c \
			ft_new_process.c \
			ft_check_argv.c \
			ft_buildtin_gmb.c \
			ft_color.c \
			ft_cleaner.c \
			ft_env_care.c \
			ft_vorpalblade_snickersnack.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_PATH = ./obj/

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

LIB_PATH = ./libft/

LIB_NAME = libft.a

INC_PATH = ./include/

INC = $(addprefix -I, $(INC_PATH))

NAME = ft_minishell1

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all : lib $(NAME)

lib :
	make -C $(LIB_PATH) re
	cp $(LIB_PATH)$(LIB_NAME) .

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(LIB_NAME) $(OBJ) -g

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(LIB) $(INC) -o $@ -c $< -g

clean :
	make -C $(LIB_PATH) clean
	rm -fv $(OBJ)
	rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean : clean
	make -C $(LIB_PATH) fclean
	rm -fv $(NAME)
	rm -fv $(LIB_NAME)

re : fclean all

norme :
	norminette $(SRC)
	norminette $(INC_PATH)*.h
