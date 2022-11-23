/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:29:09 by bperron           #+#    #+#             */
/*   Updated: 2022/11/23 09:06:48 by bperron          ###   ########.fr       */
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

int	ft_strlen_until_pipe(t_vars *vars)
{
	int	singles;
	int	doubles;
	int	i;

	singles = 0;
	doubles = 0;
	i = -1;
	while (vars->cmd[++i])
	{
		if (vars->cmd[i] == '"')
			doubles++;
		if (vars->cmd[i] == '\'')
			singles++;
		if (vars->cmd[i] == '|' && singles % 2 == 0 && doubles % 2 == 0)
			return (i);
	}
	return (i);
}

void	put_pipe(t_vars *vars, int *i, int *nb_pipe)
{
	vars->piped[*i] = ft_calloc(sizeof(char), 2);
	vars->piped[*i][0] = '|';
	*i += 1;
	*nb_pipe -= 1;
}

void	check_pipe(t_vars *vars, int size)
{
	int	i;
	int	j;
	int	k;
	int	nb_pipe;

	nb_pipe = 1;
	find_nb_pipe(vars, &nb_pipe);
	vars->piped = ft_calloc(sizeof(char *), nb_pipe + 1);
	i = 0;
	while (nb_pipe-- >= 1)
	{
		k = ft_strlen_until_pipe(vars);
		j = 0;
		vars->piped[i++] = ft_substr(vars->cmd, 0,
				ft_strlen_until_pipe(vars));
		if (nb_pipe >= 1)
			put_pipe(vars, &i, &nb_pipe);
		while (j++ <= k)
			vars->cmd++;
		while (*vars->cmd == ' ' && *vars->cmd)
			vars->cmd++;
	}
	while (size-- >= 0)
		vars->cmd--;
	free(vars->cmd);
}
