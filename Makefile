# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 13:16:40 by bperron           #+#    #+#              #
#    Updated: 2022/12/22 11:36:50 by fleduc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Werror -Wall -Wextra -g
RM = rm -rf

NAME = minishell

LIBFT = @$(MAKE) -sC ./libft
LIBFTA = ./libft/libft.a

HEADERS = include/minishell.h
SRCS = src/minishell.c src/signal.c src/utils.c src/parsing.c src/utils4.c src/built_in.c src/find_cmd.c src/utils3.c src/cd_pwd.c src/exit.c src/export_utils.c src/echo.c src/check_pipe.c src/change_var.c src/split_args.c src/utils2.c src/inspector_steve.c src/split_args_utils.c src/remove_quotes.c src/check_if_pipes.c src/pipe_cmd.c src/free.c src/redir.c src/heredoc.c src/check_redir.c src/check_redir_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(OBJS) $(HEADERS)
	$(LIBFT)
	#$(CC) $(CFLAGS) -lreadline -L $(HOME)/.brew/opt/readline/lib -I $(HOME)/.brew/opt/readline/include $(LIBFTA) $(OBJS) -o $(NAME)
	$(CC) $(CFLAGS) -lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib -I /opt/homebrew/Cellar/readline/8.2.1/include $(LIBFTA) $(OBJS) -o $(NAME)
	echo "Mandatory compilation done"
	echo "Mandatory compilation done"

clean:
	$(LIBFT) clean
	$(RM) $(OBJS) $(OBJS_BONUS)
	echo "Clean done"

fclean:	clean
	$(LIBFT) fclean
	$(RM) $(NAME)
	echo "Fclean done"

re:	fclean all

noshell:
	echo "	———————————No Shell?––———————————"
	echo "	⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝"
	echo "	⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇"
	echo "	⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏"
	echo "	 ⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁"
	echo "	⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉"
	echo "	⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂"
	echo "	⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂"
	echo "	⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁"
	echo "	⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏"
	echo "	⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝"
	echo "	⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟"
	echo "	⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟"
	echo "	⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋"
	echo "	—————————————————————————————–––"

.PHONY: all clean fclean re noshell

.SILENT: all $(NAME) clean fclean $(OBJS) noshell
