# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsotty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:44:40 by gsotty            #+#    #+#              #
#    Updated: 2017/04/04 15:40:14 by gsotty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAG = -Wall -Wextra -Werror

LIBFT = ./libft

FT_PRINTF = ./ft_printf

INCLUDE = ./minishell.h

SRC = add_env.c \
	  cd.c \
	  creat_env.c \
	  echo.c \
	  env.c \
	  exe_cmd.c \
	  ft_strsplit_space.c \
	  remove_env.c \
	  setenv.c \
	  test.c \
	  unsetenv.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -s -C $(LIBFT) re
	make -s -C $(FT_PRINTF) re
	$(CC) $(FLAG) $(SRC) ./libft/libft.a ./ft_printf/libftprintf.a -o $(NAME)

debug: $(OBJ)
	make -s -C $(LIBFT) re
	make -s -C $(FT_PRINTF) re
	$(CC) -g $(FLAG) $(SRC) ./libft/libft.a ./ft_printf/libftprintf.a -o \
		$(NAME)
	make -s -C $(LIBFT) clean
	make -s -C $(FT_PRINTF) clean
	rm -Rf $(OBJ)

%.o : %.c
	$(CC) $(FLAG) -g -c $<

clean:
	make -C $(LIBFT) clean
	make -C $(FT_PRINTF) clean
	rm -Rf $(OBJ)

declean:
	make -C $(LIBFT) fclean
	make -C $(FT_PRINTF) fclean
	rm -Rf $(NAME).dSYM
	rm -Rf $(NAME)


fclean: clean
	make -C $(LIBFT) fclean
	make -C $(FT_PRINTF) fclean
	rm -Rf $(NAME)

re: fclean all
