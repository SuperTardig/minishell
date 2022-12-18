/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:43:52 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/18 14:20:37 by fleduc           ###   ########.fr       */
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
