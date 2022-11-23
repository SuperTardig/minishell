/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:32:04 by bperron           #+#    #+#             */
/*   Updated: 2022/11/23 08:15:07 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_arrarr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr[i]);
	free(arr);
}

int	find_var_len(t_vars *vars, int env_place)
{
	char	*hold;

	hold = vars->env[env_place];
	while (*hold != '=')
		hold++;
	hold++;
	return (ft_strlen(hold));
}

int	cmd_not_found(t_vars *vars)
{
	if (ft_strcmp(vars->args[0], ">") == 0 || ft_strcmp(vars->args[0], "<") == 0
		|| ft_strcmp(vars->args[0], ">>") == 0
		|| ft_strcmp(vars->args[0], "<<") == 0)
		return (0);
	else if (vars->path == NULL && (vars->path_to_take == 9
			|| vars->path_to_take == 4))
	{
		free_pipe_args(vars);
		printf("command not found: %s\n", vars->piped[vars->index]);
		vars->last_status = 1;
		while (vars->piped[vars->index]
			&& ft_strcmp(vars->piped[vars->index], "|") != 0)
			++(vars->index);
		while (vars->piped[vars->index]
			&& ft_strcmp(vars->piped[vars->index], "|") == 0)
			++(vars->index);
		--(vars->nb_pipe);
		return (1);
	}
	return (0);
}

int	redir_check(t_vars *vars, int i)
{
	i--;
	while (i >= 0 && (vars->cmd[i] == ' ' || vars->cmd[i] == '\''
			|| vars->cmd[i] == '\"'))
		i--;
	if (i >= 1)
		if (vars->cmd[i - 1] == '<' && vars->cmd[i] == '<')
			return (0);
	return (1);
}

int	ft_argsize(char **args)
{
	int	arg;
	int	j;
	int	max;

	arg = 0;
	j = 0;
	if (args[j])
	{
		max = ft_arrsize(args);
		while (j < max)
		{
			if (args[j][0] == '|' || args[j][0] == '<'
				|| args[j][0] == '>')
				break ;
			arg++;
			j++;
		}
	}
	return (arg);
}
