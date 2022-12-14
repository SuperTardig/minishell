/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:34:29 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/22 12:40:36 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "readline.h"
# include "rlconf.h"
# include "history.h" 
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
	char			*h_cmd;
	char			*cmd;
	char			*path;
	char			**env;
	char			**new_env;
	char			**piped;
	char			**args;
	char			**redir_args;
	int				is_malloc;
	int				index;
	int				last_status;
	int				row;
	int				singles;
	int				doubles;
	int				path_to_take;
	int				last_var;
	int				nb_pipe;
	int				fd_pipe[2];
	int				redir_fd[2];
	int				redirs;
	t_split			split;
	t_list			*garbage;
}	t_vars;

//signal.c
void		sighandlerc(int signum);
void		signal_handling(void);
void		sighush(int signum);

//parsing.c
void		parsing(t_vars *vars);
void		del_spaces2(t_vars *vars);
int			ft_exec(char *cmd);
void		exec_cmd(t_vars *vars);
void		find_the_cmd(char *cmd, t_vars *vars);

//built_in.c
void		ft_env(t_vars *vars);
void		ft_export(t_vars *vars);
void		ft_unset(t_vars *vars);
void		create_new_env2(t_vars *vars, int row, int size);
void		check_if_good(t_vars *vars, int row, int *size, int *args);

//echo.c
void		ft_echo(t_vars *vars);
int			check2(t_vars *vars, int row);
void		print(t_vars *vars, int row);
int			check_flags(t_vars *vars, int *row);

//export_utils.c
int			check_if_exist(t_vars *vars, int row);
void		create_new_env(t_vars *vars, int row);
void		sort_env(t_vars *vars);
void		print_sorted(char **sorted);
void		sorting(char **sorted, int size);

//cd_pwd.c
void		ft_pwd(t_vars *vars);
void		change_pwd(char *old, char *new, t_vars *vars);
void		ft_cd(t_vars *vars);
char		*find_path(t_vars *vars);
void		ft_cd(t_vars *vars);

//exit.c
int			check_arg(char *arg);
void		set_status(t_vars *vars, unsigned char *status);
void		ft_exit(t_vars *vars);

//utils.c
void		remove_var(t_vars *vars, int var_place, int size);
void		free_garbage(t_vars *vars, int status);
int			cmp(char *cmp, char *try);
void		init_redirs(t_vars *vars);
void		good_file(t_vars *vars);

//utils2.c
void		free_arrarr(char **arr);
int			find_var_len(t_vars *vars, int env_place);
int			redir_check(t_vars *vars, int i);
int			cmd_not_found(t_vars *vars);
int			ft_argsize(char **args);

//utils3.c
int			redirections3(t_vars *vars, int i);
int			redirections2(t_vars *vars, int i);
int			bad_access(t_vars *vars, int i);
int			valid_exec(t_vars *vars);
int			check_char(char *str, char c);

//utils4.c
int			ft_charchr(char *str, int c);
void		ft_cutstr(t_vars *vars, int start, int end);
void		piper2(t_vars *vars);
void		ft_status(t_vars *vars, int i, int j, int k);
void		dup_for_exec(t_vars *vars);

//find_cmd.c
char		*look_path(t_vars *vars, char *cmd);
char		*look_path2(t_vars *vars, char *cmd);
char		**get_args(t_vars *vars, int start);

//check_pipe.c
void		check_pipe(t_vars *vars, int i, int x);
int			ft_strlen_until_pipe(char *cmd);
void		find_nb_pipe(t_vars *vars, int *nb);
void		put_pipe(t_vars *vars, int *i, int *nb_pipe);

//check_redir.c
void		check_redir(t_vars *vars);
char		*new_str(t_vars *vars, int *j, int *i);
char		*help_redir(t_vars *vars, int *j, int *k);
int			find_size(char *str, int i, int doubles, int singles);

//check_redir_utils.c
int			count_redir(t_vars *vars, int singles, int doubles);
int			redir_count(char *str, int *j, int *singles, int *doubles);

//split_args.c
void		split_args(t_vars *vars);
int			size_find(t_vars *vars, int row, int start);
void		splitter(t_vars *vars, char **new_piped, int i, int j);
void		splitter2(t_vars *vars, int i, int *j, char **new_piped);

//split_args_utils.c
int			count_args(t_vars *vars, int nb);
void		reset_counters(int *i, int *j, int *l, int *k);
void		reset_counters2(int *i, int *j, int *l);
void		do_plus_plus(int *i, int *j);

//remove_quotes.c
void		remove_quotes(t_vars *vars, int i, int single, int doubles);
void		check_quotes(char c, int *single, int *doubles);
int			find_nb_quotes(char *cmd);

//change_var.c
void		find_var(t_vars *vars, int i);
void		loop_var(t_vars *vars, int i, int d_quotes, int quotes);
void		status(t_vars *vars, int i, int j, int k);
void		change_var(t_vars *vars, int var_place, int env_place, int len);
int			put_new_var(t_vars *vars, char *new, int var_place, int env_place);

//check_if_pipes.c
void		check_if_pipes(t_vars *vars);
void		loop_index(t_vars *vars);
int			check_pipes_syntax(t_vars *vars);

//pipe_cmd.c
void		piper(t_vars *vars);
pid_t		do_fork(void);
void		do_pipe(t_vars *vars);
void		dumpling(t_vars *vars, pid_t pid);
void		do_execve(t_vars *vars, pid_t pid);

//heredoc.c
int			heredoc(t_vars *vars, int i);
void		loop_the_var(t_vars *vars, int i);
void		find_the_var(t_vars *vars, int i);
void		change_the_var(t_vars *vars, int var_place, int env_i, int len);
int			put_the_new_var(t_vars *vars, char *new, int var_place, int env_place);

//inspector_steve.c
int			del_spaces(t_vars *vars);
int			quotes_error(int quote, int dquote);
void		rm_spaces(t_vars *vars, int len, int quote_pos, int dquote_pos);
int			search_quotes(t_vars *vars, int quote_pos, int dquote_pos, int i);

//redir.c
int			redirections(t_vars *vars);
void		duplicate(t_vars *vars);
int			redir_len(t_vars *vars);
void		make_redir_args(t_vars *vars, int j);

//minishell.c
int			main(int argc, char **argv, char **envp);
int			ft_readline(t_vars *vars);

//free.c
void		free_pipe_args(t_vars *vars);

#endif
