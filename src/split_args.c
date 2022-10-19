/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:32:58 by bperron           #+#    #+#             */
/*   Updated: 2022/10/19 10:52:20 by bperron          ###   ########.fr       */
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

int	find_size(t_vars *vars, int row, int start)
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
		{
			quotes++;
			doubles++;
		}
		if (vars->piped[row][i] == '\'' && doubles % 2 == 0)
		{
			quotes++;
			singles++;
		}
		if (vars->piped[row][i] == ' ' && quotes % 2 == 0)
			return (i - start);
		i++;
	}
	return (i - start);
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
	int	dquotes;

	l = 0;
	k = 0;
	quotes = 0;
	dquotes = 0;
	while (vars->piped[i])
	{
		if (!(new_piped[k]))
			new_piped[k] = ft_calloc(find_size(vars, i, j) + 100,
					sizeof(char));
		if (vars->piped[i][j] == '"' && quotes % 2 == 0)
			dquotes++;
		if (vars->piped[i][j] == '\'' && dquotes % 2 == 0)
			quotes++;
		new_piped[k][l++] = vars->piped[i][j++];
		if (vars->piped[i][j] == ' ' && quotes % 2 == 0 && dquotes % 2 == 0)
		{
			l = 0;
			k++;
			while (vars->piped[i][j] == ' ')
				j++;
		}
		if (!(vars->piped[i][j]))
		{
			reset_counters(&i, &j, &l);
		}
	}
}

void	split_args(t_vars *vars)
{
	char	**new_piped;
	int		j;

	new_piped = ft_calloc(count_args(vars, 1) + 1, sizeof(char *));
	j = 0;
	while (vars->piped[0][j] == ' ')
		j++;
	splitter(vars, new_piped, 0, j);
	free_arrarr(vars->piped);
	vars->piped = new_piped;
	remove_quotes(vars, 0);
}
