/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:34:29 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/20 10:13:24 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../readline/readline.h"
# include "../readline/history.h" 
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../libft/ft_fprintf/ft_fprintf.h"

typedef struct s_parse {
	int		pipes;
	char	*red;
	char	**cmd_sep;
}	t_parse;

typedef struct s_vars{
	char	**env;
	char	*cmd;
	char	*metas;
	int		cmd_len;
	int		cmd_len_each;
	int		path_to_take;
	int		i_cmd;
	int		i_meta;
	int		last_status;
	t_parse	parse;
}	t_vars;

//signal.c
void	signal_handling(void);
void	sighandler(int signum);
void	sighandlerc(int signum);

//parsing.c
int		meta_num(char *cmd);
void	ft_strtok(t_vars *vars);
void	parsing(t_vars *vars);

//built_in.c
void	ft_echo(t_vars *vars);
void	ft_pwd(t_vars *vars);
void	ft_cd(t_vars *vars);
void	ft_export(t_vars *vars);
void	find_cmd(t_vars *vars);
void	ft_unset(t_vars *vars);
void	ft_env(t_vars *vars);

//exit.c
int		check_arg(t_vars *vars);
void	set_status(t_vars *vars, unsigned char *status);
void	ft_exit(t_vars *vars);

//utils.c
int		check_args(t_vars *vars);
void	go_to_next(t_vars *vars);

//find_cmd.c
char	*look_path(t_vars *vars, char *cmd);
char	*get_cmd(t_vars *vars);
void	find_cmd(t_vars *vars);
void	mini_pipe(t_vars *vars, char *path);

//inspector_steve.c (before strtok())
void	before_tok(t_vars *vars);

#endif
