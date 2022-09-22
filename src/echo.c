/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:24:02 by bperron           #+#    #+#             */
/*   Updated: 2022/09/22 11:16:23 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_flags(t_vars *vars)
{
	char	*hold;
	int		temp;
	int		flags;
	int		i;

	flags = 0;
	temp = vars->i_cmd;
	hold = vars->cmd;
	go_to_next(vars);
	while (vars->cmd[0] == '-')
	{
		i = 0;
		while (vars->cmd[++i])
		{
			if (vars->cmd[i] != 'n' && vars->cmd[i] != 'e')
			{
				vars->i_cmd = temp;
				vars->cmd = hold;
				return (flags);
			}
		}
		flags = 1;
		go_to_next(vars);
	}
	return (flags);
}

void	print(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->cmd_len - 1 > vars->i_cmd)
	{
		printf("%s", vars->cmd);
		while (vars->cmd[i++])
			vars->i_cmd++;
		while (!(vars->cmd[i++]) && vars->i_cmd < vars->cmd_len - 1)
		{
			if (vars->metas[vars->i_meta] != ' ')
				break ;
			else
				printf(" ");
			vars->i_cmd++;
			vars->i_meta++;
		}
		go_to_next(vars);
	}
}

void	ft_echo(t_vars *vars)
{
	int	flags;

	flags = check_flags(vars);
	if (flags == 0)
	{
		print(vars);
		printf("\n");
	}
	else
		print(vars);
}
