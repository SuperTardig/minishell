/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:40:21 by bperron           #+#    #+#             */
/*   Updated: 2022/10/07 15:31:54 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen_until(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
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

void	go_to_next(t_vars *vars)
{
	while (vars->i_cmd < vars->cmd_len && vars->cmd[0])
	{
		vars->cmd++;
		vars->i_cmd++;
	}
	while (vars->i_cmd < vars->cmd_len && vars->cmd[0] == '\0')
	{
		if (vars->cmd[0] == '\0')
			vars->i_meta++;
		vars->i_cmd++;
		vars->cmd++;
	}
	vars->i_cmd++;
}

int	check_meta(t_vars *vars, char meta)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (vars->metas[i])
	{
		if (vars->metas[i] == meta)
			num++;
		++i;
	}
	return (num);
}
