/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:30:44 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/17 14:10:52 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	duplicate(t_vars *vars)
{
	int	j;

	j = -1;
	if (vars->redir_fd[0] != 0)
	{
		dup2(vars->redir_fd[0], STDIN_FILENO);
		close(vars->redir_fd[0]);
	}
	else if (vars->redir_fd[1] != 1)
	{
		dup2(vars->redir_fd[1], STDOUT_FILENO);
		close(vars->redir_fd[1]);
	}
	if (vars->redirs != -1)
	{
		vars->redir_args = ft_calloc(vars->redirs + 1, sizeof(char *));
		while (++j < vars->redirs)
			vars->redir_args[j] = vars->args[j];
	}
}

void	redirections(t_vars *vars)
{
	int	i;

	i = -1;
	vars->redirs = -1;
	vars->redir_fd[0] = 0;
	vars->redir_fd[1] = 1;
	if (vars->redir_args)
		free(vars->redir_args);
	while (vars->args[++i])
	{
		if (ft_strcmp(vars->args[i], ">") == 0)
		{
			if (vars->redirs == -1)
				vars->redirs = i;
			if (vars->redir_fd[1] != 1)
				close(vars->redir_fd[1]);
			vars->redir_fd[1] = open(vars->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (ft_strcmp(vars->args[i], "<") == 0)
		{
			if (vars->redirs == -1)
				vars->redirs = i;
			if (vars->redir_fd[0] != 0)
				close(vars->redir_fd[0]);
			vars->redir_fd[0] = open(vars->args[i + 1], O_RDONLY);
		}
		else if (ft_strcmp(vars->args[i], ">>") == 0)
		{
			if (vars->redirs == -1)
				vars->redirs = i;
			if (vars->redir_fd[1] != 1)
				close(vars->redir_fd[1]);
			vars->redir_fd[1] = open(vars->args[i + 1], O_WRONLY
					| O_APPEND | O_CREAT, 0644);
		}
		else if (ft_strcmp(vars->args[i], "<<") == 0)
		{
			if (vars->redirs == -1)
				vars->redirs = i;
			if (vars->redir_fd[0] != 0)
				close(vars->redir_fd[0]);
			vars->redir_fd[0] = heredoc(vars, i);
		}
	}
}
