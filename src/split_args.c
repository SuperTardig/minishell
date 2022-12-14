/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:32:58 by bperron           #+#    #+#             */
/*   Updated: 2022/12/22 12:30:21 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	size_find(t_vars *vars, int row, int start)
{
	int	i;
	int	quotes;
	int	singles;
	int	doubles;

	i = start;
	quotes = 0;
	singles = 0;
	doubles = 0;
	while (vars->piped[row][i])
	{
		if (vars->piped[row][i] == '"' && singles % 2 == 0)
			do_plus_plus(&quotes, &doubles);
		if (vars->piped[row][i] == '\'' && doubles % 2 == 0)
			do_plus_plus(&quotes, &singles);
		if (vars->piped[row][i] == ' ' && quotes % 2 == 0)
			return (i - start);
		i++;
	}
	return (i - start);
}

void	splitter2(t_vars *vars, int i, int *j, char **new_piped)
{
	vars->split.ok = 0;
	if (!(new_piped[vars->split.k]))
			new_piped[vars->split.k] = ft_calloc(size_find(vars, i, *j) + 1,
				sizeof(char));
	if (vars->piped[i][*j] == '"' && vars->singles % 2 == 0)
		vars->doubles++;
	if (vars->piped[i][*j] == '\'' && vars->doubles % 2 == 0)
		vars->singles++;
}

void	splitter(t_vars *vars, char **new_piped, int i, int j)
{
	vars->split.k = 0;
	vars->split.l = 0;
	vars->singles = 0;
	vars->doubles = 0;
	while (vars->piped[i])
	{
		splitter2(vars, i, &j, new_piped);
		new_piped[vars->split.k][vars->split.l++] = vars->piped[i][j++];
		if (vars->piped[i][j] == ' '
				&& vars->singles % 2 == 0 && vars->doubles % 2 == 0)
		{
			vars->split.l = 0;
			vars->split.k++;
			vars->split.ok = 1;
			while (vars->piped[i][j] == ' ')
				j++;
		}
		if (!(vars->piped[i][j]))
		{
			if (vars->split.ok == 0)
				reset_counters(&i, &j, &vars->split.l, &vars->split.k);
			else
				reset_counters2(&i, &j, &vars->split.l);
		}
	}
}

void	split_args(t_vars *vars)
{
	char	**new_piped;
	int		j;

	new_piped = ft_calloc(count_args(vars, 1
				+ vars->nb_pipe), sizeof(char *));
	j = 0;
	while (vars->piped[0][j] == ' ')
		j++;
	splitter(vars, new_piped, 0, j);
	free_arrarr(vars->piped);
	vars->piped = new_piped;
	remove_quotes(vars, 0, 0, 0);
}
