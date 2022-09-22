/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:09:52 by bperron           #+#    #+#             */
/*   Updated: 2022/09/22 13:49:06 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_vars *vars)
{
	int	i;

	i = -1;
	while (vars->env[++i])
		printf("%s\n", vars->env[i]);
}

void	ft_export(t_vars *vars)
{
	int		args;

	args = check_args(vars);
	if (args >= 1)
	{
		while (args >= 1)
		{
			go_to_next(vars);
			if (ft_strchr(vars->cmd, '='))
			{	
				if (check_if_exist(vars) == 0)
					create_new_env(vars);
			}
			args--;
		}
	}
	else if (args == 0)
		sort_env(vars);
}

void	create_new_env2(t_vars *vars, char **new_env)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (vars->env[++i])
	{
		if (ft_strncmp(vars->cmd, vars->env[i], ft_strlen(vars->cmd)) == 0)
			i++;
		new_env[++j] = vars->env[i];
	}
	new_env[++j] = 0;
	vars->env = new_env;
}

void	ft_unset(t_vars *vars)
{
	char	**new_env;
	int		size;
	int		i;

	i = -1;
	go_to_next(vars);
	size = ft_arrsize(vars->env);
	while (vars->env[++i])
	{
		if (ft_strncmp(vars->cmd, vars->env[i], ft_strlen(vars->cmd)) == 0)
		{
			size--;
			break ;
		}
	}
	new_env = ft_calloc(sizeof(char *), size);
	create_new_env2(vars, new_env);
}
