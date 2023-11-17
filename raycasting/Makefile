# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/29 11:26:19 by hasalam           #+#    #+#              #
#    Updated: 2023/11/02 15:59:24 by hasalam          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = Cub3d.c

CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g
MLXF = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
LIBMLX = MLX42/build/libmlx42.a

I = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
L = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)


%.o: %.c Cub3d.h
	$(CC) $(FLAGS) -o $@ -c $< $(I)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(MLXF) $(OBJS) $(LIBMLX) $(L) $(I) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx