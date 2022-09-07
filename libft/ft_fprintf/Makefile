# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperron <bperron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 13:24:27 by fleduc            #+#    #+#              #
#    Updated: 2022/09/07 11:18:58 by bperron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftfprintf.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf
AR = ar rcs

SRCS = ft_fprintf.c ft_fformat_p.c ft_fformat_x_u.c ft_fformat_d_i.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean re all
