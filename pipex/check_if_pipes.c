/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/26 15:57:03 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	exec_pipe(t_vars *vars, int c_pipes)
{
	int	i;

	i = 0;
	if (pipe(vars->fd_pipe) == -1)
	{
		printf("Could not make a pipe\n");
		exit(1);
	}
	while (c_pipes >= 0)
	{
		find_the_cmd(vars->piped[i], vars, i);
		if (vars->path_to_take != 9)
			pipe_builtin(vars, c_pipes);
		else
			pipe_cmd(vars, c_pipes, i);
		while (vars->piped[i] && ft_strcmp(vars->piped[i], "|") != 0)
			++i;
		if (vars->piped[i] && ft_strcmp(vars->piped[i], "|") == 0)
			++i;
		--c_pipes;
	}
	close(vars->fd_pipe[0]);
	close(vars->fd_pipe[1]);
}*/

void	check_if_pipes(t_vars *vars)
{
	/*if (vars->nb_pipe == 0)
	{
		find_the_cmd(vars->piped[0], vars, 0);
		exec_cmd(vars);
	}*/
	vars->index = 0;
	piper(vars, -1);
}
