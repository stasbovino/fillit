# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/15 15:08:42 by gwyman-m          #+#    #+#              #
#    Updated: 2019/04/13 19:42:48 by gwyman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

FLAGS = -Wall -Wextra -Werror -g

LIBFT = -L libft/ -lft

CFILES = main.c check_valid.c get_figure.c read_figure.c map.c fillit.c \
		 position.c place_del_figure.c equal_figures.c mapr_opts.c \
		 mapr_start.c

SRC_DIR = sourses/

SRC = $(addprefix $(SRC_DIR),$(CFILES))

OBJ = $(CFILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(SRC_DIR)fillit.h
	make -C libft
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT)

$(OBJ): $(SRC)
	gcc $(FLAGS) -c $(SRC) -Ilibft/includes

clean:
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all
