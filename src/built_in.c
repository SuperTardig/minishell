/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:09:52 by bperron           #+#    #+#             */
/*   Updated: 2022/10/19 10:49:45 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_vars *vars)
{
	int	i;

	i = -1;
	if (ft_arrsize(vars->piped) == 1)
		while (vars->env[++i])
			printf("%s\n", vars->env[i]);
	else
	{
		vars->row++;
		errno = 2;
		ft_fprintf(2, "cd: %s: ", vars->piped[vars->row]);
		perror("");
	}
}

void	ft_export(t_vars *vars)
{
	int		args;

	args = ft_arrsize(vars->piped);
	if (args > 1)
	{
		while (args > 1)
		{
			vars->row++;
			if (ft_strchr(vars->piped[vars->row], '='))
			{	
				if (check_if_exist(vars) == 0)
					create_new_env(vars);
			}
			args--;
		}
	}
	else
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
		if (ft_strncmp(vars->piped[vars->row], vars->env[i],
				ft_strlen(vars->piped[vars->row])) == 0)
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
	size = ft_arrsize(vars->env);
	if (ft_arrsize(vars->piped) > 1)
	{
		vars->row++;
		while (vars->env[++i])
		{
			if (ft_strncmp(vars->piped[vars->row], vars->env[i],
					ft_strlen(vars->piped[vars->row])) == 0)
			{
				size--;
				break ;
			}
		}
		new_env = ft_calloc(sizeof(char *), size);
		create_new_env2(vars, new_env);
	}
	else
	{
		ft_fprintf(2, "unset: not enough arguments\n");
	}
}
