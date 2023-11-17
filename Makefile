# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 19:40:18 by ebennix           #+#    #+#              #
#    Updated: 2023/11/17 18:50:39 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := cub3d

ARCH := lib/lib_42.a

CC := cc 

CFLAGS := -g -Wall -Wextra 
# -Werror -Imlx 

HEADER := cuba/inc/cub3d.h		cuba/inc/structs.h		cuba/inc/defin.h \

FILES := cuba/main \
		 cuba/parse/read_map \
		 cuba/parse/Interpreter \
		 cuba/parse/fields_analyzer \
		 cuba/parse/map_evaluator \
		#  cuba/loader/ 	\
		#  cuba/tools/parse_tools \
		#  cuba/tools/free_game \

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := MakefileAutoPush

########################################################################

all : $(EXE)

library:
	make -C lib

$(EXE) : $(OBJ)
	$(CC)  $(OBJ) $(ARCH) -o $(EXE) -lreadline

# -lmlx -framework OpenGL -o

%.o : %.c $(HEADER) | library
	$(CC) $(CFLAGS) -c -o $@ $<

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

########################################################################

.PHONY : all clean fclean re git
