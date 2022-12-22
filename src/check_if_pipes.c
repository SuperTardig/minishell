/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/22 12:12:05 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_pipes_syntax(t_vars *vars)
{
	int	i;

	i = -1;
	if (ft_strcmp(vars->piped[0], "|") == 0)
	{
		printf("Minishell: syntax error near unexpected token '|'\n");
		vars->last_status = 1;
		return (1);
	}
	while (vars->piped[++i + 1])
	{
		if (ft_strcmp(vars->piped[i], vars->piped[i + 1]) == 0)
		{
			printf("Minishell: syntax error near unexpected token '|'\n");
			vars->last_status = 1;
			return (1);
		}
	}
	return (0);
}

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

	find_the_cmd(vars->piped[0], vars);
	if (ft_strcmp(vars->piped[0], "") == 0
		|| ft_strcmp(vars->piped[0], ".") == 0)
		return ;
	if (vars->nb_pipe == 0 && (vars->path_to_take == 0
			|| vars->path_to_take == 1 || vars->path_to_take == 2
			|| vars->path_to_take == 3 || vars->path_to_take == 6))
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
