/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:09:56 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/01 13:56:16 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*look_path2(t_vars *vars, char *cmd)
{
	char	*path;
	char	*slash_path;
	char	**sep_path;
	int		i;

	i = 0;
	while (ft_strnstr(vars->env[i], "PATH=", 5) == NULL)
		++i;
	sep_path = ft_split(vars->env[i] + 5, ':');
	i = -1;
	while (sep_path[++i])
	{
		slash_path = ft_strjoin(sep_path[i], "/");
		path = ft_strjoin(slash_path, cmd);
		free(slash_path);
		if (access(path, F_OK) == 0)
		{
			free_arrarr(sep_path);
			return (path);
		}
		free(path);
	}
	free_arrarr(sep_path);
	return (NULL);
}

char	*look_path(t_vars *vars, char *cmd)
{
	int	i;

	i = -1;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (vars->env[++i])
		if (ft_strnstr(vars->env[i], "PATH=", 5) != NULL)
			return (look_path2(vars, cmd));
	return (NULL);
}

char	**get_args(t_vars *vars, int start)
{
	char	**args;
	int		i;
	int		j;
	int		k;

	i = start;
	while (vars->piped[i] && ft_strcmp(vars->piped[i], "|") != 0)
		++i;
	i -= start;
	args = ft_calloc(i + 1, sizeof(char *));
	j = -1;
	while (++j < i)
		args[j] = ft_calloc
			(ft_strlen(vars->piped[start + j]) + 1, sizeof(char));
	j = -1;
	while (++j < i)
	{
		k = -1;
		while (++k < (int)ft_strlen(vars->piped[start + j]))
			args[j][k] = vars->piped[start + j][k];
	}
	return (args);
}
