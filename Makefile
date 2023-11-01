# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 19:40:18 by ebennix           #+#    #+#              #
#    Updated: 2023/11/01 19:48:47 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := cub3d

ARCH := lib/lib_42.a

CC := cc 

CFLAGS := -g -Wall -Werror -Wextra 

HEADER := Mandatory/inc/cub3d.h

FILES := Mandatory/cub3d \
		 Mandatory/utils/ \
		 Mandatory/parse/ \

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

%.o : %.c $(HEADER) | library
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

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
