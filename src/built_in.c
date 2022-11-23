/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:09:52 by bperron           #+#    #+#             */
/*   Updated: 2022/11/23 10:21:14 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_vars *vars)
{
	int	i;

	i = -1;
	if (ft_argsize(vars->piped) == 1)
		while (vars->env[++i])
			printf("%s\n", vars->env[i]);
	else
	{
		errno = 2;
		ft_fprintf(2, "env: %s: ", vars->piped[vars->index + 1]);
		perror("");
	}
}

void	ft_export(t_vars *vars)
{
	int		args;
	int		row;

	row = vars->index;
	args = ft_argsize(vars->piped);
	if (args > 1)
	{
		while (args > 1 && vars->piped[row][0] != '|')
		{
			row++;
			if (ft_strchr(vars->piped[row], '='))
			{	
				if (check_if_exist(vars, row) == 0)
					create_new_env(vars, row);
			}
			args--;
		}
		vars->is_malloc = 1;
	}
	else
		sort_env(vars);
}

void	create_new_env2(t_vars *vars, int row, int size)
{
	char	**new_env;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new_env = ft_calloc(sizeof(char *), size + 1);
	while (vars->env[++i])
	{
		if (ft_strncmp(vars->piped[row], vars->env[i],
				ft_strlen(vars->piped[row])) == 0)
			i++;
		new_env[++j] = vars->env[i];
	}
	new_env[++j] = 0;
	if (vars->is_malloc == 1)
		free_arrarr(vars->env);
	vars->env = new_env;
}

void	check_if_good(t_vars *vars, int row, int *size, int *args)
{
	int	i;

	i = -1;
	while (vars->env[++i])
	{
		if (ft_strncmp(vars->piped[row], vars->env[i],
				ft_strlen(vars->piped[row])) == 0)
		{
			*size -= 1;
			*args -= 1;
			return ;
		}
	}
}

void	ft_unset(t_vars *vars)
{
	int		row;
	int		size;
	int		args;

	row = vars->index + 1;
	args = ft_argsize(vars->piped);
	if (args > 1)
	{
		while (args > 1 && vars->piped[row][0] != '|')
		{
			size = ft_arrsize(vars->env);
			check_if_good(vars, row, &size, &args);
			create_new_env2(vars, row, size);
			row++;
		}
	}
}
