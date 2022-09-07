/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:40:21 by bperron           #+#    #+#             */
/*   Updated: 2022/08/31 10:49:35 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_args(t_vars *vars)
{
	int	args;
	int	i;

	args = 0;
	i = 0;
	while (i < vars->cmd_len)
	{
		if (vars->cmd[i] == '\0')
			if (vars->metas[vars->i_meta++] == ' ')
				if (vars->cmd[i + 1] != '\0')
					args++;
		i++;
	}
	return (args);
}

int	cmp(char *cmd, char *try)
{
	int	i;

	i = 0;
	while (cmd[i] && try[i] && cmd[i] == try[i])
		i++;
	if (cmd[i] || try[i])
		return (0);
	return (1);
}
