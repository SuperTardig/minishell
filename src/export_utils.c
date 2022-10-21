/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:05:24 by bperron           #+#    #+#             */
/*   Updated: 2022/10/20 13:15:50 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_exist(t_vars *vars)
{
	int	size;
	int	i;

	size = ft_strlen_until(vars->piped[vars->row], '=');
	i = -1;
	while (vars->env[++i])
	{
		if (ft_strlen_until(vars->piped[vars->row], '=')
			== ft_strlen_until(vars->env[i], '='))
		{
			if (ft_strncmp(vars->piped[vars->row], vars->env[i], size) == 0)
			{
				vars->env[i] = ft_substr(vars->piped[vars->row], 0,
						ft_strlen(vars->piped[vars->row]));
				return (1);
			}
		}
	}	
	return (0);
}

void	create_new_env(t_vars *vars)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (vars->env[i])
		i++;
	new_env = ft_calloc(i + 3, sizeof(char *));
	while (++j < i - 1)
		new_env[j] = vars->env[j];
	new_env[j] = ft_substr(vars->piped[vars->row], 0,
			ft_strlen(vars->piped[vars->row]));
	new_env[j + 1] = vars->env[j];
	new_env[j + 2] = NULL;
	vars->env = new_env;
}

void	print_sorted(char **sorted)
{
	int	i;

	i = -1;
	while (sorted[++i])
	{
		ft_fprintf(1, "declare -x ");
		while (*sorted[i] != '=')
			ft_putchar_fd(*sorted[i]++, 1);
		ft_putchar_fd(*sorted[i]++, 1);
		ft_fprintf(1, "\"%s\"\n", sorted[i]);
	}
}

void	sorting(char **sorted, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - 1 - i)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
			{
				temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
		}
	}
}

void	sort_env(t_vars *vars)
{
	int		size;
	int		i;
	char	**sorted;

	size = 0;
	while (vars->env[size])
		size++;
	sorted = ft_calloc(size, sizeof(char *));
	i = -1;
	while (vars->env[++i])
		sorted[i] = vars->env[i];
	sorting(sorted, size);
	print_sorted(sorted);
}
