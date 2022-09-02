# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperron <bperron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 09:41:33 by fleduc            #+#    #+#              #
#    Updated: 2022/09/02 09:07:16 by bperron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
FLAGS = -Wall -Werror -Wextra -g
RM = rm -f

LIB = ar rcs
PRINTF = ft_printf
FPRINTF = ft_fprintf

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	   ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	   ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	   ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	   ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_atoll.c \
	   ft_strcmp.c get_next_line.c

OBJS = $(SRCS:.c=.o)

SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -sC $(PRINTF)
	$(MAKE) -sC $(FPRINTF)
	cp $(PRINTF)/libftprintf.a .
	mv libftprintf.a libft.a
	cp $(FPRINTF)/libftfprintf.a .
	mv libftfprintf.a libft.a
	$(LIB) $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS_BONUS)
	$(LIB) $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
	$(MAKE) -sC $(PRINTF) clean
	$(MAKE) -sC $(FPRINTF) clean
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(MAKE) -sC $(PRINTF) fclean
	$(MAKE) -sC $(FPRINTF) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
