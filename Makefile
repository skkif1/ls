#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/23 14:48:31 by omotyliu          #+#    #+#              #
#    Updated: 2017/02/23 14:48:35 by omotyliu         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc


NAME = ft_ls

FT_LS_SRC = ft_ls.c print.c sort.c util.c get_info.c parse_param.c \
            get_attributes.c get_attributes_n.c parse_folder.c

OBJECTS = $(subst .c,.o,$(FT_LS_SRC))

all: $(NAME)

$(NAME):
	make -C libft
	gcc -o $(NAME) $(FT_LS_SRC) libft/*.o

clean:
	make clean -C libft
	rm -f OBJECTS

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all