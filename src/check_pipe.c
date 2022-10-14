/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:29:09 by bperron           #+#    #+#             */
/*   Updated: 2022/10/14 13:33:28 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_pipe(t_vars *vars)
{
	int	i;
	int	nb_pipe;

	i = -1;
	vars->nb_pipe = 0;
	while (vars->cmd[++i])
		if (vars->cmd[i] == '|')
			vars->nb_pipe++;
	vars->piped = ft_calloc(sizeof(char *), vars->nb_pipe + 2);
	i = 0;
	nb_pipe = vars->nb_pipe;
	while (nb_pipe-- >= 0)
	{
		vars->piped[i++] = ft_substr(vars->cmd, 0,
				ft_strlen_until(vars->cmd, '|'));
		while (*vars->cmd != '|' && *vars->cmd)
			vars->cmd++;
		vars->cmd++;
		while (*vars->cmd == ' ' && *vars->cmd)
			vars->cmd++;
	}
	vars->piped[i] = NULL;
}

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

void	remove_quotes(t_vars *vars, int i)
{
	int		single;
	int		doubles;
	int		j;
	int		k;
	char	**with_out;

	while (vars->piped[i])
		i++;
	with_out = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	single = 0;
	doubles = 0;
	while (vars->piped[++i])
	{
		with_out[i] = ft_calloc(sizeof(char),
				ft_strlen(vars->piped[i]) - find_nb_quotes(vars->piped[i]) + 1);
		j = -1;
		k = -1;
		while (vars->piped[i][++j])
		{	
			if (vars->piped[i][j] == '"' && single % 2 == 0)
				doubles++;
			if (vars->piped[i][j] == '\'' && doubles % 2 == 0)
				single++;
			if ((vars->piped[i][j] == '"' && single % 2 == 1) || (vars->piped[i][j] == '\'' && doubles % 2 == 1))
				with_out[i][++k] = vars->piped[i][j];
			if (vars->piped[i][j] != '"' && vars->piped[i][j] != '\'')
				with_out[i][++k] = vars->piped[i][j];
		}
	}
	free_arrarr(vars->piped);
	vars->piped = with_out;
}
