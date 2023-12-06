# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 19:40:18 by ebennix           #+#    #+#              #
#    Updated: 2023/12/06 17:42:10 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := cub3d
B_EXE := cub3d_bonus

ARCH := lib/lib_42.a

MLX_ARCH = MLX42/build/libmlx42.a

CC := cc -Ofast

CFLAGS := -g -Wall -Wextra -Werror 

MLXFLAGS := -framework Cocoa -framework OpenGL -framework IOKit -lglfw

I = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
L = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib

M_HEADER := Mandatory/inc/cub3d.h		Mandatory/inc/structs.h		Mandatory/inc/defin.h \
B_HEADER := Bonus/inc/cub3d.h			Bonus/inc/structs.h			Bonus/inc/defin.h \

M_FILES := Mandatory/main \
		 Mandatory/parse/read_file \
		 Mandatory/parse/Interpreter \
		 Mandatory/parse/fields_analyzer \
		 Mandatory/parse/map_evaluator \
		 Mandatory/loader/init_textures \
		 Mandatory/loader/events \
		 Mandatory/tools/free_game \
		 Mandatory/tools/cub_tools \
		 Mandatory/tools/ray_tools \
		 Mandatory/graphics/draw3d \
		 Mandatory/graphics/raycasting \
		 Mandatory/graphics/raycast_helper \

B_FILES := Bonus/main \
		 Bonus/parse/read_file \
		 Bonus/parse/Interpreter \
		 Bonus/parse/fields_analyzer \
		 Bonus/parse/map_evaluator \
		 Bonus/loader/init_textures \
		 Bonus/loader/events \
		 Bonus/tools/free_game \
		 Bonus/tools/draw_tools \
		 Bonus/tools/cub_tools \
		 Bonus/tools/ray_tools \
		 Bonus/graphics/draw3d \
		 Bonus/graphics/raycasting \
		 Bonus/graphics/raycast_helper \
		 Bonus/graphics/mini_map \
		 Bonus/graphics/sprites \

M_SRC := $(M_FILES:=.c)
M_OBJ := $(M_SRC:.c=.o)

B_SRC := $(B_FILES:=.c)
B_OBJ := $(B_SRC:.c=.o)

RM := rm -rf
m := finished

########################################################################

all : $(EXE)

bonus : $(B_EXE)

library:
	make -C lib

$(EXE): $(M_OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(M_OBJ) $(ARCH) $(MLX_ARCH) $(L) $(I) -o $(EXE)

$(B_EXE) : $(B_OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(B_OBJ) $(ARCH) $(MLX_ARCH) $(L) $(I) -o $(B_EXE)

%.o : %.c $(HEADER) | library
	$(CC) $(CFLAGS) -c -o $@ $< $(I)

clean :
	make clean -C lib
	$(RM) $(M_OBJ)
	$(RM) $(B_OBJ)

fclean : clean
	make fclean -C lib
	$(RM) $(EXE)
	$(RM) $(B_EXE)

re : fclean all

git :
	make fclean
	git add .
	git status
	git commit -m "$(m)"
	git push
	make

########################################################################

.PHONY : all bonus clean fclean re git
