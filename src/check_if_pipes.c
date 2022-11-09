/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/09 12:01:30 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	loop_index(t_vars *vars)
{
	while (vars->piped[vars->index]
		&& ft_strcmp(vars->piped[vars->index], "|") != 0)
			++(vars->index);
	while (vars->piped[vars->index]
		&& ft_strcmp(vars->piped[vars->index], "|") == 0)
			++(vars->index);
}

void	check_if_pipes(t_vars *vars)
{
	pid_t	pid2;

	find_the_cmd(vars->piped[0], vars, 0);
	if (vars->nb_pipe == 0 && (vars->path_to_take == 0
			|| vars->path_to_take == 1 || vars->path_to_take == 2
			|| vars->path_to_take == 3))
		exec_cmd(vars);
	else
	{
		vars->index = 0;
		pid2 = fork();
		piper(vars, pid2);
		if (pid2 == 0)
			exit(1);
		wait(&pid2);
	}
}
