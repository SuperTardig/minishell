/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/21 14:08:52 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_builtin(t_vars *vars, int c_pipes)
{
	if (c_pipes == vars->nb_pipe)
	{
		dup2(vars->fd_pipe[1], STDOUT_FILENO);
		exec_cmd(vars);
	}
	else if (c_pipes == 0)
	{
		dup2(vars->fd_pipe[0], STDIN_FILENO);
		exec_cmd(vars);
	}
	else
	{
		dup2(vars->fd_pipe[1], STDOUT_FILENO);
		dup2(vars->fd_pipe[0], STDIN_FILENO);
		exec_cmd(vars);
	}
}

void	pipe_cmd(t_vars *vars, int c_pipes, int cmd)
{
	if (c_pipes == vars->nb_pipe)
	{
		dup2(vars->fd_pipe[1], STDOUT_FILENO);
		its_piping_time(vars, look_path(vars, vars->piped[cmd]), cmd);
	}
	else if (c_pipes == 0)
	{
		dup2(vars->fd_pipe[0], STDIN_FILENO);
		its_piping_time(vars, look_path(vars, vars->piped[cmd]), cmd);
	}
	else
	{
		dup2(vars->fd_pipe[1], STDOUT_FILENO);
		dup2(vars->fd_pipe[0], STDIN_FILENO);
		its_piping_time(vars, look_path(vars, vars->piped[cmd]), cmd);
	}
}

void	exec_pipe(t_vars *vars, int c_pipes)
{
	int	i;

	i = 0;
	while (c_pipes >= 0)
	{
		find_the_cmd(vars->piped[i], vars);
		if (vars->path_to_take != 8)
			pipe_builtin(vars, c_pipes);
		else
			pipe_cmd(vars, c_pipes, i);
		while (ft_strcmp(vars->piped[i], "|") == 0 && vars->piped[i])
			++i;
		--c_pipes;
	}
}

void	check_if_pipes(t_vars *vars)
{
	int	c_pipes;

	c_pipes = vars->nb_pipe;
	if (vars->nb_pipe == 0)
	{
		find_the_cmd(vars->piped[0], vars);
		exec_cmd(vars);
	}
	else
	{
		if (pipe(vars->fd_pipe) == -1)
			return ;
		exec_pipe(vars, c_pipes);
		close(vars->fd_pipe[0]);
		close(vars->fd_pipe[1]);
	}
}