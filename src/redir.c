/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:30:44 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/07 11:05:40 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	duplicate(t_vars *vars, int *fd, int i, int fileno)
{
	int	j;

	j = -1;
	dup2(*fd, fileno);
	close(*fd);
	vars->redir_args = ft_calloc(i + 1, sizeof(char *));
	while (++j < i)
		vars->redir_args[j] = vars->args[j];
}

void	redirections(t_vars *vars)
{
	int	i;
	int	fd;

	i = -1;
	if (vars->redir_args)
		free(vars->redir_args);
	while (vars->args[++i]
		&& ft_strcmp(vars->args[i], "|") != 0
		&& vars->args[i])
	{
		if (ft_strcmp(vars->args[i], ">") == 0)
		{
			fd = open(vars->args[i + 1], O_WRONLY | O_CREAT, 0644);
			duplicate(vars, &fd, i, 1);
			break ;
		}
		else if (ft_strcmp(vars->args[i], "<") == 0)
		{
			fd = open(vars->args[i + 1], O_RDONLY);
			duplicate(vars, &fd, i, 0);
			break ;
		}
		else if (ft_strcmp(vars->args[i], ">>") == 0)
		{
			fd = open(vars->args[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
			duplicate(vars, &fd, i, 1);
			break ;
		}
		else if (ft_strcmp(vars->args[i], "<<") == 0)
		{
			fd = open(vars->args[i + 1], O_RDONLY | O_APPEND);
			duplicate(vars, &fd, i, 0);
			break ;
		}
	}
}
