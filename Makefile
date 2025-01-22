# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 00:11:18 by leobarbo          #+#    #+#              #
#    Updated: 2025/01/14 23:34:21 by leobarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := cub3d
CC          := gcc
CFLAGS      := -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3 -fPIC
LIBFT       := ./lib/libft
LIBMLX42_PATH := ./lib/MLX42
LIBMLX_REPO := https://github.com/codam-coding-college/MLX42.git
SRCS_PATH   := ./src/
OBJ_PATH    := ./obj
.SILENT:

GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

HEADERS     := -I ./include -I $(LIBMLX42_PATH)/include -I $(LIBFT)/include
LIBS        := ${LIBFT}/libft.a $(LIBMLX42_PATH)/build/libmlx42.a -lglfw -ldl -lXext -lX11 -lm
SRCS        := $(shell find $(SRCS_PATH) -type f -name "*.c")
OBJS        := $(patsubst $(SRCS_PATH)%.c,$(OBJ_PATH)/%.o,$(SRCS))

all: $(OBJ_PATH) libmlx42 libft $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRCS_PATH)%.c | $(OBJ_PATH)
	@mkdir -p $(@D)
	$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $<

libft:
	@$(MAKE) -C $(LIBFT)

$(LIBMLX42_PATH):
	@git clone $(LIBMLX_REPO) $(LIBMLX42_PATH)

libmlx42: $(LIBMLX42_PATH)
	cmake -S $(LIBMLX42_PATH) -B $(LIBMLX42_PATH)/build
	make -C $(LIBMLX42_PATH)/build -j4

$(NAME): $(OBJS)
	printf "$(YELLOW)Compiling...$(RESET)\n"
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	printf "$(GREEN)Done!$(RESET)\n"

clean:
	rm -rf $(OBJ_PATH)
	rm -rf $(LIBMLX42_PATH)/build

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx42 libft
