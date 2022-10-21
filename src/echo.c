/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:24:02 by bperron           #+#    #+#             */
/*   Updated: 2022/10/20 13:42:01 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check2(t_vars *vars, int *i)
{
	while (vars->piped[vars->row][++*i])
	{
		if (vars->piped[vars->row][*i] != 'n')
			return (1);
	}
	return (0);
}

int	check_flags(t_vars *vars)
{
	int		flags;
	int		hold;
	int		i;

	flags = 0;
	hold = vars->row;
	if (ft_arrsize(vars->piped) > 1)
	{
		hold = ++vars->row;
		i = 0;
		while (vars->piped[vars->row])
		{
			if (vars->piped[vars->row][0] == '-')
			{
				if (check2(vars, &i) == 1)
					return (flags);
				flags = 1;
				hold++;
			}
			vars->row++;
		}
		vars->row++;
	}
	vars->row = hold;
	return (flags);
}

void	print(t_vars *vars)
{
	int	arg;

	if (ft_arrsize(vars->piped) > 1)
	{
		arg = ft_arrsize(vars->piped) - vars->row - 2;
		while (arg-- > -1)
			if (vars->piped[vars->row] != NULL)
				printf("%s ", vars->piped[vars->row++]);
		printf("%s", vars->piped[vars->row]);
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
