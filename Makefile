# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 14:59:17 by tsantana          #+#    #+#              #
#    Updated: 2024/11/18 15:37:37 by tsantana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Cub3D

CFLAGS	= -Wextra -Wall -Werror -g3

LIBMLX	= ./libs/MLX42/

SRC_P	= ./src/

HEADERS	= -I $(LIBMLX)/include -I ./include/

LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	= $(addprefix $(SRC_P), teste.c render_minimap.c controls.c free.c render_background.c)

OBJS	= $(addprefix obj/, $(notdir $(SRCS:.c=.o)))

BUILD	= obj/

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

obj:
	mkdir -p $(BUILD)

obj/%.o: $(SRC_P)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): obj $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BUILD)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
