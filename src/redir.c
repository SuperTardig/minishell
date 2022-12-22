/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:30:44 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/22 12:37:14 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_len(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->args[i + 2] && (ft_strcmp(vars->args[i + 2], "<<") != 0
			&& ft_strcmp(vars->args[i + 2], ">>") != 0
			&& ft_strcmp(vars->args[i + 2], "<") != 0
			&& ft_strcmp(vars->args[i + 2], ">") != 0))
		++i;
	return (i);
}

void	make_redir_args(t_vars *vars, int j)
{
	if (vars->redirs != -1)
	{
		if (ft_strcmp(vars->args[0], "<<") == 0
			|| ft_strcmp(vars->args[0], ">>") == 0
			|| ft_strcmp(vars->args[0], "<") == 0
			|| ft_strcmp(vars->args[0], ">") == 0)
		{
			if (vars->args[2] && (ft_strcmp(vars->args[2], "<<") != 0
					|| ft_strcmp(vars->args[2], ">>") != 0
					|| ft_strcmp(vars->args[2], "<") != 0
					|| ft_strcmp(vars->args[2], ">") != 0))
				vars->path = look_path(vars, vars->args[2]);
			vars->redir_args = ft_calloc(redir_len(vars) + 1, sizeof(char *));
			while (++j < redir_len(vars))
				vars->redir_args[j] = vars->args[j + 2];
		}
		else
		{
			vars->redir_args = ft_calloc(vars->redirs + 1, sizeof(char *));
			while (++j < vars->redirs)
				vars->redir_args[j] = vars->args[j];
		}
	}
}

void	duplicate(t_vars *vars)
{
	int	j;

	j = -1;
	if (vars->redir_fd[0] != 0)
	{
		dup2(vars->redir_fd[0], STDIN_FILENO);
		close(vars->redir_fd[0]);
	}
	if (vars->redir_fd[1] != 1)
	{
		dup2(vars->redir_fd[1], STDOUT_FILENO);
		close(vars->redir_fd[1]);
	}
	make_redir_args(vars, j);
}

int	redirections(t_vars *vars)
{
	int	i;

	i = -1;
	init_redirs(vars);
	while (vars->args[++i])
	{
		if (ft_strcmp(vars->args[i], ">") == 0)
		{
			if (vars->redirs == -1)
				vars->redirs = i;
			if (vars->redir_fd[1] != 1)
				close(vars->redir_fd[1]);
			if (bad_access(vars, i))
				return (1);
			vars->redir_fd[1] = open(vars->args[i + 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (ft_strcmp(vars->args[i], ">>") == 0
			|| ft_strcmp(vars->args[i], "<<") == 0
			|| ft_strcmp(vars->args[i], "<") == 0)
			if (redirections2(vars, i))
				return (1);
	}
	duplicate(vars);
	return (0);
}
