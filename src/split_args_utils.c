/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:23:07 by bperron           #+#    #+#             */
/*   Updated: 2022/10/21 11:20:44 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_args(t_vars *vars, int nb)
{
	int	i;
	int	j;

	i = -1;
	while (vars->piped[++i])
	{
		j = -1;
		while (vars->piped[i][++j])
		{
			if (vars->piped[i][j] == '"')
			{
				while (vars->piped[i][++j] != '"')
					(void) j;
			}
			else if (vars->piped[i][j] == '\'')
			{
				while (vars->piped[i][++j] != '\'')
					(void) j;
			}
			if (vars->piped[i][j] == ' ')
				nb++;
		}
		nb++;
	}
	return (nb);
}

void	reset_counters(int *i, int *j, int *l, int *k)
{
	*i += 1;
	*j = 0;
	*l = 0;
	*k += 1;
}

void	reset_counters2(int *i, int *j, int *l)
{
	*i += 1;
	*j = 0;
	*l = 0;
}

void	do_plus_plus(int *i, int *j)
{
	*i += 1;
	*j += 1;
}
