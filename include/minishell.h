/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:34:29 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/25 12:44:56 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../readline/readline.h"
# include "../readline/rlconf.h"
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

typedef struct s_spilt{
	int	ok;
	int	k;
	int	l;
}	t_split;

typedef struct s_vars{
	char			**env;
	char			**new_env;
	char			**piped;
	char			*cmd;
	char			*metas;
	int				last_status;
	int				row;
	int				singles;
	int				doubles;
	int				i_cmd;
	int				cmd_len_each;
	int				path_to_take;
	int				i_meta;
	int				variables;
	int				is_malloc;
	int				is_meta;
	int				last_var;
	int				nb_pipe;
	int				fd_pipe[2];
	t_split			split;
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
void	ft_env(t_vars *vars);
void	ft_export(t_vars *vars);
void	create_new_env2(t_vars *vars, char **new_env);
void	ft_unset(t_vars *vars);

//echo.c
void	ft_echo(t_vars *vars);

//export_utils.c
int		check_if_exist(t_vars *vars);
void	create_new_env(t_vars *vars);
void	sort_env(t_vars *vars);

//cd_pwd.c
void	ft_pwd(t_vars *vars);
void	ft_cd(t_vars *vars);

//exit.c
int		check_arg(char *arg);
void	set_status(t_vars *vars, unsigned char *status);
void	ft_exit(t_vars *vars);

//utils.c
int		ft_strlen_until(char *str, char c);
int		cmp(char *cmp, char *try);
int		check_args(t_vars *vars);
void	go_to_next(t_vars *vars);

//utils2.c
void	free_arrarr(char **arr);
int		find_var_len(t_vars *vars, int env_place);

//find_cmd.c
char	*look_path(t_vars *vars, char *cmd);
char	*get_cmd(t_vars *vars);
void	find_cmd(t_vars *vars);

//variables.c
char	*get_cmd2(t_vars *vars);
void	variables(t_vars *vars);
void	del_spaces(t_vars *vars);
void	change_variables(t_vars *vars);

//check_pipe.c
void	check_pipe(t_vars *vars);

//split_args.c
void	split_args(t_vars *vars);

//split_args_utils.c
int		count_args(t_vars *vars, int nb);
void	reset_counters(int *i, int *j, int *l, int *k);
void	reset_counters2(int *i, int *j, int *l);
void	do_plus_plus(int *i, int *j);

//remove_quotes.c
void	remove_quotes(t_vars *vars, int i, int single, int doubles);

//change_var.c
void	find_var(t_vars *vars, int i);
void	loop_var(t_vars *vars, int i, int d_quotes, int quotes);

void	its_piping_time(t_vars *vars, char *path, int start);
void	check_if_pipes(t_vars *vars);
void	exec_cmd(t_vars *vars);
void	find_the_cmd(char *cmd, t_vars *vars, int index);
void	rm_exec(t_vars *vars, int index);

#endif
