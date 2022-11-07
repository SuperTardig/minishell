/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:43:52 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/07 10:28:42 by bperron          ###   ########.fr       */
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
