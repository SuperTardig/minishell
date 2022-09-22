/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:53:16 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/07 11:00:36 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_cmd(t_vars *vars)
{
	int		i;
	char	*cmd;

	i = 0;
	while (vars->cmd[vars->i_cmd + i])
		++i;
	cmd = malloc(sizeof(char) * i + 1);
	i = 0;
	while (vars->cmd[vars->i_cmd + i])
	{
		cmd[i] = vars->cmd[vars->i_cmd + i];
		++i;
	}
	return (cmd);
}

void	variables(t_vars *vars)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = get_cmd(vars);
	if (get_env(cmd))
		printf("%s", cmd);
	else
		printf("variable does not exist\n");
	free(cmd);
}
