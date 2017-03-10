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

CC = gcc -Wall -Wextra -Werror


NAME = ft_ls

FT_LS_SRC = ft_ls.c print.c sort.c util.c get_info.c parse_param.c \
            get_attributes.c get_attributes_n.c parse_folder.c

OBJECTS = $(subst .c,.o,$(FT_LS_SRC))

$(NAME): $(OBJECTS)
	@make -C libft/
	gcc $(OBJECTS) -o $(NAME) libft/libftprintf.a


all: $(NAME)

clean: 
	@make -C libft/ clean
	rm -rf $(OBJECTS)

fclean: clean
	@make -C libft/ fclean
	rm -rf $(NAME) $(OBJECTS)

re: fclean all