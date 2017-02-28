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
CFLAGS = -Wall -Wextra -Werror
NAME = ft_ls.a

SRCFLS = ft_ls.c print.c sort.c

PRINTF_OBJ = $(subst .c,.o,$(PRINTF_SRC))
OBJECTS = $(subst .c,.o,$(SRCFLS))
SRC_C = $(SRCFLS:%=libft/%) $(PRINTF_SRC)
SRC_O = $(SRC_C:.c=.o) $(PRINTF_OBJ)
all: $(NAME)

$(NAME): $(SRC_O)
	ar rc $(NAME) $(SRC_O)
	ranlib $(NAME)

$(OBJECT): $(SRC_C)
	gcc -Wall -Wextra -Werror -c $(SRC_C)
clean:
	/bin/rm -f $(SRC_O)
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all
