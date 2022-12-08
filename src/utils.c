/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:40:21 by bperron           #+#    #+#             */
/*   Updated: 2022/12/08 12:45:07 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmp(char *cmd, char *try)
{
	int	i;

	i = 0;
	while (cmd[i] && try[i] && cmd[i] == try[i])
		i++;
	if (cmd[i] || try[i])
		return (0);
	return (1);
}

void	free_garbage(t_vars *vars, int status)
{
	t_list	*hold;

	if (vars->is_malloc == 1)
		free(vars->env);
	if (vars->cmd)
		free(vars->cmd);
	if (vars->piped)
		free_arrarr(vars->piped);
	if (vars->garbage)
	{
		hold = vars->garbage;
		while (hold != NULL)
		{
			hold = vars->garbage->next;
			free(vars->garbage->content);
			free(vars->garbage);
			vars->garbage = hold;
		}
	}
	exit(status);
}

void	remove_var(t_vars *vars, int var_place, int size)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(vars->cmd) - size + 1, sizeof(char));
	i = -1;
	j = -1;
	while (vars->cmd[++i])
	{
		if (i == var_place)
		{
			while (size--)
				i++;
		}
		new[++j] = vars->cmd[i];
	}
	free(vars->cmd);
	vars->cmd = new;
	loop_var(vars, -1, 0, 0);
}

void	init_redirs(t_vars *vars)
{
	vars->redirs = -1;
	vars->redir_fd[0] = 0;
	vars->redir_fd[1] = 1;
}

void	good_file(t_vars *vars)
{
	if (redirections(vars))
	{
		exit(1);
	}	
}
