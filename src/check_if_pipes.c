/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/07 10:20:19 by fleduc           ###   ########.fr       */
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

	vars->index = 0;
	pid2 = fork();
	piper(vars, pid2);
	if (pid2 == 0)
		exit(1);
	wait(&pid2);
}
