/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:40:21 by bperron           #+#    #+#             */
/*   Updated: 2022/08/30 11:03:15 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_prompt(void)
{
	static int	first_open = 1;

	if (first_open == 1) //check for first time opening command prompt
	{
		printf("\e[1;1H\e[2J"); //clear screen
		first_open = 0;
	}
	printf("\e[0;29mMinishell >"); //command line
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
