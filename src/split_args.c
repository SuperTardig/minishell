/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:32:58 by bperron           #+#    #+#             */
/*   Updated: 2022/10/12 10:21:56 by bperron          ###   ########.fr       */
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
			else if (vars->piped[i][j] == ' ')
				nb++;
		}
	}
	return (nb);
}

int	find_size(t_vars *vars, int row)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (vars->piped[row][++i])
	{
		if (vars->piped[row][i] == '"' || vars->piped[row][i] == '\'')
			quotes++;
		if (vars->piped[row][i] == ' ' && (quotes % 2) != 0)
			return (i);
	}
	return (i);
}

void	reset_counters(int *i, int *j, int *l)
{
	*i += 1;
	*j = 0;
	*l = 0;
}

void	splitter(t_vars *vars, char **new_piped, int i, int j)
{
	int	k;
	int	l;
	int	quotes;

	l = 0;
	k = 0;
	quotes = 0;
	while (vars->piped[i])
	{
		if (vars->piped[i][j] == ' ' && (quotes % 2) != 1)
		{
			l = 0;
			k++;
			while (vars->piped[i][j] == ' ')
				j++;
		}
		if (vars->piped[i][j] == '"' || vars->piped[i][j] == '\'')
			quotes++;
		if (!(new_piped[k]))
			new_piped[k] = ft_calloc(find_size(vars, i) + 1, sizeof(char));
		new_piped[k][l++] = vars->piped[i][j++];
		if (!(vars->piped[i][j]))
			reset_counters(&i, &j, &l);
	}
}

void	split_args(t_vars *vars)
{
	char	**new_piped;
	int		j;

	new_piped = ft_calloc(count_args(vars, 1) + 2, sizeof(char *));
	j = 0;
	while (vars->piped[0][j] == ' ')
		j++;
	splitter(vars, new_piped, 0, j);
	free_arrarr(vars->piped);
	vars->piped = new_piped;
	remove_quotes(vars, 0, 0);
}
