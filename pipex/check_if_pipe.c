/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/19 11:55:22 by fleduc           ###   ########.fr       */
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

void	pipe_cmd(t_vars *vars)
{
	
}

void	exec_pipe(t_vars *vars, int c_pipes)
{
	int	i;

	i = 0;
	while (c_pipes >= 0)
	{
		find_path(vars->piped[i]);
		if (vars->path_to_take != 8)
			pipe_builtin(vars, c_pipes);
		else
			pipe_cmd(vars);
		//i_do_piping(vars);
		
		while (vars->piped[i] != '|' && vars->piped[i])
			++i;
		--c_pipes;
	}
}

void	check_if_pipe(t_vars *vars)
{
	int	c_pipes;

	c_pipes = vars->nb_pipe;
	if (vars->nb_pipe == 0)
	{
		find_path(vars->piped[0], vars);
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