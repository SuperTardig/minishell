/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:43:52 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/22 12:40:03 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_pipe_args(t_vars *vars)
{
	int	i;

	i = -1;
	while (vars->args[++i])
		free(vars->args[i]);
	free(vars->args);
	free(vars->path);
	vars->args = NULL;
	vars->path = NULL;
}
