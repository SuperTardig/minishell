/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:24:02 by bperron           #+#    #+#             */
/*   Updated: 2022/11/22 13:37:19 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check2(t_vars *vars, int row)
{
	int	i;

	i = 0;
	while (vars->piped[row][++i])
	{
		if (vars->piped[row][i] != 'n')
			return (1);
	}
	return (0);
}

int	check_flags(t_vars *vars, int *row)
{
	int		flags;
	int		hold;

	flags = 0;
	hold = *row;
	if (ft_argsize(vars->piped) > 1)
	{
		hold = ++*row;
		while (vars->piped[*row])
		{
			if (vars->piped[*row][0] == '-')
			{
				if (check2(vars, *row) == 1)
					return (flags);
				flags = 1;
				hold++;
			}
			*row += 1;
		}
		*row += 1;
	}
	*row = hold;
	return (flags);
}

void	print(t_vars *vars, int row)
{
	int	arg;

	if (ft_argsize(vars->piped) > 1)
	{
		arg = ft_argsize(vars->piped) - row - 2;
		while (arg-- > -1)
			if (vars->piped[row] != NULL && vars->piped[row][0] != '|')
				printf("%s ", vars->piped[row++]);
		if (vars->piped[row][0] != '|')
			printf("%s", vars->piped[row]);
	}
}

void	ft_echo(t_vars *vars)
{
	int	flags;
	int	row;

	row = vars->index;
	flags = check_flags(vars, &row);
	if (flags == 0)
	{
		print(vars, row);
		printf("\n");
	}
	else
		print(vars, row);
}
