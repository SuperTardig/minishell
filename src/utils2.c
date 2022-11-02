/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:32:04 by bperron           #+#    #+#             */
/*   Updated: 2022/11/02 14:16:55 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_arrarr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr[i]);
	free(arr);
}

int	cmd_not_found(t_vars *vars)
{
	if (vars->path == NULL)
	{
		free_pipe_args(vars);
		printf("command not found: %s\n", vars->piped[vars->index]);
		vars->last_status = 1;
		while (vars->piped[vars->index]
			&& ft_strcmp(vars->piped[vars->index], "|") != 0)
			++(vars->index);
		while (vars->piped[vars->index]
			&& ft_strcmp(vars->piped[vars->index], "|") == 0)
			++(vars->index);
		--(vars->nb_pipe);
		return (1);
	}
	return (0);
}
