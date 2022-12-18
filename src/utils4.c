/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:04:15 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/18 12:26:02 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_charchr(char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

void	ft_cutstr(t_vars *vars, int start, int end)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = ft_calloc(ft_strlen(vars->h_cmd)
			- (end - start + 1) + 1, sizeof(char));
	i = -1;
	while (++i < start)
		new_str[i] = vars->h_cmd[i];
	j = end;
	while (++j < (int)ft_strlen(vars->h_cmd))
		new_str[i++] = vars->h_cmd[j];
	new_str[i] = '\0';
	free(vars->h_cmd);
	vars->h_cmd = new_str;
}

void	piper2(t_vars *vars)
{
	pid_t	pid;

	if (vars->nb_pipe != 0)
		do_pipe(vars);
	pid = do_fork();
	if (vars->nb_pipe != 0)
		dumpling(vars, pid);
	do_execve(vars, pid);
	free_pipe_args(vars);
	vars->nb_pipe -= 1;
}

void	ft_status(t_vars *vars, int i, int j, int k)
{
	char	*nb;
	char	*new;

	nb = ft_itoa(vars->last_status);
	new = ft_calloc(ft_strlen(vars->h_cmd) + ft_strlen(nb) - 1, sizeof(char));
	while (vars->h_cmd[++i] != '$' && vars->h_cmd[i + 1] != '?')
		new[++j] = vars->h_cmd[i];
	i += 1;
	while (nb[++k])
		new[++j] = nb[k];
	while (vars->h_cmd[++i])
		new[++j] = vars->h_cmd[i];
	free(vars->h_cmd);
	free(nb);
	vars->h_cmd = new;
	loop_the_var(vars, -1);
}

void	dup_for_exec(t_vars *vars)
{
	if (vars->nb_pipe != 0)
	{
		dup2(vars->fd_pipe[0], STDIN_FILENO);
		close(vars->fd_pipe[0]);
		close(vars->fd_pipe[1]);
	}
}
