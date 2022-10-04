/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:23:26 by bperron           #+#    #+#             */
/*   Updated: 2022/10/04 11:01:52 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_cmd2(t_vars *vars)
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
	if (getenv(cmd))
		printf("%s", cmd);
	else
		printf("variable does not exist\n");
	free(cmd);
}
