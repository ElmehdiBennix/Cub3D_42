# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 19:40:18 by ebennix           #+#    #+#              #
#    Updated: 2023/12/01 20:03:23 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := cub3d

ARCH := lib/lib_42.a

MLX_ARCH = MLX42/build/libmlx42.a

CC := cc -Ofast

CFLAGS := -g -Wall -Wextra -fsanitize=address
# -Werror 

MLXFLAGS := -framework Cocoa -framework OpenGL -framework IOKit -lglfw

I = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
L = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib

HEADER := cuba/inc/cub3d.h		cuba/inc/structs.h		cuba/inc/defin.h \

FILES := cuba/main \
		 cuba/parse/read_file \
		 cuba/parse/Interpreter \
		 cuba/parse/fields_analyzer \
		 cuba/parse/map_evaluator \
		 cuba/loader/init_textures \
		 cuba/loader/events \
		 cuba/tools/free_game \
		 cuba/tools/draw_tools \
		 cuba/tools/cub_tools \
		 cuba/tools/ray_tools \
		 cuba/graphics/draw3d \
		 cuba/graphics/raycasting \
		 cuba/graphics/mini_map \
		 cuba/graphics/sprites \

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := almost finished

########################################################################

all : $(EXE)

library:
	make -C lib

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJ) $(ARCH) $(MLX_ARCH) $(L) $(I) -o $(EXE)

%.o : %.c $(HEADER) | library
	$(CC) $(CFLAGS) -c -o $@ $< $(I)

clean :
	make clean -C lib
	$(RM) $(OBJ)

fclean : clean
	make fclean -C lib
	$(RM) $(EXE)

re : fclean all

git :
	make fclean
	git add .
	git status
	git commit -m "$(m)"
	git push
	make

########################################################################

.PHONY : all clean fclean re git


# if i change smthing in lib it dosnt remake fix it later