# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgras <mgras@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/31 15:31:03 by mgras             #+#    #+#              #
#    Updated: 2015/04/08 15:25:32 by mgras            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/

SRC_NAME =	ft_chldabs.c \
			ft_cleaner.c \
			ft_color.c \
			ft_core.c \
			ft_env.c \
			ft_get_next_line.c \
			ft_lexseur.c \
			ft_lex_mcr.c \
			ft_correction_center.c \
			ft_scan_error.c \
			ft_iswhat.c \
			ft_path_maker.c \
			ft_prex.c \
			ft_setenv.c \
			ft_unsetenv.c \

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_PATH = ./obj/

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

LIB_PATH = ./libft/

LIB_NAME = libft.a

INC_PATH = ./include/

INC = $(addprefix -I, $(INC_PATH))

NAME = ft_minishell2

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all : lib $(NAME)

lib :
	make -C $(LIB_PATH) re
	cp $(LIB_PATH)$(LIB_NAME) .

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ) $(LIB_NAME) -g

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $< -g

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
