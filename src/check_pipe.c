/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:29:09 by bperron           #+#    #+#             */
/*   Updated: 2022/12/22 12:18:51 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_nb_pipe(t_vars *vars, int *nb)
{
	int	i;
	int	singles;
	int	doubles;

	vars->nb_pipe = 0;
	i = -1;
	singles = 0;
	doubles = 0;
	while (vars->cmd[++i])
	{
		if (vars->cmd[i] == '|' && (singles % 2 != 1 && doubles % 2 != 1))
		{
			vars->nb_pipe++;
			*nb += 2;
		}
		else if (vars->cmd[i] == '\'')
			singles++;
		else if (vars->cmd[i] == '"')
			doubles++;
	}
}

int	ft_strlen_until_pipe(char *cmd)
{
	int	singles;
	int	doubles;
	int	i;

	singles = 0;
	doubles = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"')
			doubles++;
		if (cmd[i] == '\'')
			singles++;
		if (cmd[i] == '|' && singles % 2 == 0 && doubles % 2 == 0)
			return (i);
	}
	return (i);
}

void	put_pipe(t_vars *vars, int *i, int *nb_pipe)
{
	vars->piped[*i] = ft_calloc(2, sizeof(char));
	vars->piped[*i][0] = '|';
	vars->piped[*i][1] = '\0';
	*i += 1;
	*nb_pipe -= 1;
}

void	check_pipe(t_vars *vars, int i, int x)
{
	int	j;
	int	k;
	int	nb_pipe;

	nb_pipe = 1;
	find_nb_pipe(vars, &nb_pipe);
	vars->piped = ft_calloc(sizeof(char *), nb_pipe + 1);
	while (nb_pipe-- >= 1)
	{
		k = ft_strlen_until_pipe(&vars->cmd[x]);
		j = 0;
		if (ft_strcmp(ft_substr(&vars->cmd[x], 0,
				ft_strlen_until_pipe(&vars->cmd[x])), "") != 0)
			vars->piped[i++] = ft_substr(&vars->cmd[x], 0,
				ft_strlen_until_pipe(&vars->cmd[x]));
		if (nb_pipe >= 1)
			put_pipe(vars, &i, &nb_pipe);
		while (j++ <= k)
			x++;
		while (vars->cmd[x] == ' ' && vars->cmd[x])
			x++;
	}
}
