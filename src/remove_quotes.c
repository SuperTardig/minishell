/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:56:51 by bperron           #+#    #+#             */
/*   Updated: 2022/12/22 12:31:53 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_nb_quotes(char *cmd)
{
	int	j;
	int	quotes;
	int	single;
	int	doubles;

	j = -1;
	single = 0;
	doubles = 0;
	quotes = 0;
	while (cmd[++j])
	{
		if (cmd[j] == '"' && single % 2 == 0)
		{
			doubles++;
			quotes++;
		}
		if (cmd[j] == '\'' && doubles % 2 == 0)
		{
			single++;
			quotes++;
		}
	}
	return (quotes);
}

void	check_quotes(char c, int *single, int *doubles)
{
	if (c == '"' && *single % 2 == 0)
		*doubles += 1;
	else if (c == '\'' && *doubles % 2 == 0)
		*single += 1;
}

void	remove_quotes(t_vars *vars, int i, int single, int doubles)
{
	int		j;
	int		k;
	char	**with_out;

	with_out = ft_calloc(sizeof(char *), ft_arrsize(vars->piped) + 1);
	i = -1;
	while (vars->piped[++i])
	{	
		with_out[i] = ft_calloc(sizeof(char),
				ft_strlen(vars->piped[i]) - find_nb_quotes(vars->piped[i]) + 1);
		j = -1;
		k = -1;
		while (vars->piped[i][++j])
		{	
			check_quotes(vars->piped[i][j], &single, &doubles);
			if ((vars->piped[i][j] == '"' && single % 2 == 1)
				|| (vars->piped[i][j] == '\'' && doubles % 2 == 1))
				with_out[i][++k] = vars->piped[i][j];
			else if (vars->piped[i][j] != '"' && vars->piped[i][j] != '\'')
				with_out[i][++k] = vars->piped[i][j];
		}
	}
	free_arrarr(vars->piped);
	vars->piped = with_out;
}
