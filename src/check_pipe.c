/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:29:09 by bperron           #+#    #+#             */
/*   Updated: 2022/10/11 08:08:38 by bperron          ###   ########.fr       */
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

void	remove_quotes(t_vars *vars, int quotes, int i)
{
	int		j;
	int		k;
	char	**with_out;

	while (vars->piped[i])
		i++;
	with_out = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (vars->piped[++i])
	{
		j = -1;
		while (vars->piped[i][++j])
			if (vars->piped[i][j] == '"' || vars->piped[i][j] == '\'')
				quotes++;
		with_out[i] = ft_calloc(sizeof(char),
				ft_strlen(vars->piped[i]) - quotes + 1);
		j = -1;
		k = -1;
		while (vars->piped[i][++j])
			if (vars->piped[i][j] != '"' && vars->piped[i][j] != '\'')
				with_out[i][++k] = vars->piped[i][j];
	}
	free_arrarr(vars->piped);
	vars->piped = with_out;
}
