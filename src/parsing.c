/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:33:43 by bperron           #+#    #+#             */
/*   Updated: 2022/08/25 11:26:04 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	meta_num(char *cmd)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (cmd[++i])
	{
		if (ft_strchr(";&| ()<>-", (int) cmd[i]))
			num++;
	}
	return (num);
}

void	ft_strtok(t_vars *vars)
{
	int		i;
	int		j;

	vars->cmd_len = ft_strlen(vars->cmd);
	vars->metas = ft_calloc(sizeof(char), meta_num(vars->cmd));
	i = 0;
	j = 0;
	while (vars->cmd[i])
	{
		if (ft_strchr(";&| ()<>-", vars->cmd[i]))
		{
			vars->metas[j++] = vars->cmd[i];
			vars->cmd[i] = '\0';
		}
		i++;
	}
	vars->metas[j] = '\0';
}
