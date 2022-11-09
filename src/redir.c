/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:30:44 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/09 15:46:42 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	duplicate(t_vars *vars, int *fd, int i)
{
	int	j;

	j = -1;
	if (fd[0] != 0)
		dup2(fd[0], STDIN_FILENO);
	else if (fd[1] != 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	vars->redir_args = ft_calloc(i + 1, sizeof(char *));
	while (++j < i)
		vars->redir_args[j] = vars->args[j];
}

void	redirections(t_vars *vars)
{
	int	i;
	int	find;
	int	fd[2];

	i = -1;
	find = -1;
	fd[0] = 0;
	fd[1] = 1;
	if (vars->redir_args)
		free(vars->redir_args);
	while (vars->args[++i])
	{
		if (ft_strcmp(vars->args[i], ">") == 0)
		{
			if (find == -1)
				find = i;
			if (fd[1] != 1)
				close(fd[1]);
			fd[1] = open(vars->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (ft_strcmp(vars->args[i], "<") == 0)
		{
			if (find == -1)
				find = i;
			if (fd[0] != 0)
				close(fd[0]);
			fd[0] = open(vars->args[i + 1], O_RDONLY);
		}
		else if (ft_strcmp(vars->args[i], ">>") == 0)
		{
			if (find == -1)
				find = i;
			if (fd[1] != 1)
				close(fd[1]);
			fd[1] = open(vars->args[i + 1], O_WRONLY
					| O_APPEND | O_CREAT, 0644);
		}
		else if (ft_strcmp(vars->args[i], "<<") == 0)
		{
			if (find == -1)
				find = i;
			if (fd[0] != 0)
				close(fd[0]);
			fd[0] = heredoc(vars, i);
		}
	}
	if (find != -1)
		duplicate(vars, fd, find);
}
