/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/23 14:45:58 by fleduc           ###   ########.fr       */
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
	int		stdinout_cp[2];

	find_the_cmd(vars->piped[0], vars, 0);
	if (ft_strcmp(vars->piped[0], "") == 0
		|| ft_strcmp(vars->piped[0], ".") == 0)
		return ;
	if (vars->nb_pipe == 0 && (vars->path_to_take == 0
			|| vars->path_to_take == 1 || vars->path_to_take == 2
			|| vars->path_to_take == 3))
		exec_cmd(vars);
	else
	{
		vars->index = 0;
		stdinout_cp[1] = dup(STDOUT_FILENO);
		stdinout_cp[0] = dup(STDIN_FILENO);
		piper(vars);
		dup2(stdinout_cp[1], STDOUT_FILENO);
		dup2(stdinout_cp[0], STDIN_FILENO);
		close(stdinout_cp[0]);
		close(stdinout_cp[1]);
	}
}
