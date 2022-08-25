/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:39 by bperron           #+#    #+#             */
/*   Updated: 2022/08/25 14:24:20 by bperron          ###   ########.fr       */
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
# include "../libft/libft.h"

typedef struct s_vars{
	char	**env;
	char	*cmd;
	char	*metas;
	int		cmd_len;
	int		path_to_take;
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
void	ft_exit(t_vars *vars);
void	ft_echo(t_vars *vars);
void	ft_pwd(t_vars *vars);
void	ft_cd(t_vars *vars);
void	ft_export(t_vars *vars);
void	find_cmd(t_vars *vars);
void	ft_unset(t_vars *vars);
void	ft_env(t_vars *vars);

//utils.c
void	cmd_prompt(void);

#endif
