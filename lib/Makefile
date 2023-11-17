# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/22 04:53:15 by ebennix           #+#    #+#              #
#    Updated: 2023/11/17 20:45:20 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := lib_42.a

CFLAGS := -g -Wall -Werror -Wextra

CC := cc

HEADER := ./inc/lib_42.h   ./inc/colors.h 	

OBJ_DIR := obj_files

FILES := libft/int/ft_atoi			libft/int/ft_isalpha	 	libft/int/ft_strncmp	   		\
		 libft/int/ft_strlcpy		libft/int/ft_strlen	  		libft/int/ft_isdigit			\
		 libft/string/ft_itoa		libft/string/ft_strchr	 	libft/string/ft_strnstr			\
		 libft/heap/ft_strdup	    libft/heap/ft_split	 		libft/heap/ft_strjoin 	   		\
		 libft/heap/free2d          libft/heap/ft_strtrim		libft/heap/ft_calloc	   		\
		 libft/heap/ft_substr		\
		 libft/memory/ft_bzero	 	libft/memory/ft_memset	    libft/memory/ft_memcpy	   		\
		 gnl/get_next_line			\
		 fprintf/ft_fprintf		fprintf/utils/ft_fprintf_hex	fprintf/utils/ft_fprintf_put	\

SRC := $(FILES:=.c)
OBJ := $(SRC:.c=.o)

AR := ar -rc
RM := rm -rf


all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

.PHONY: all clean fclean
