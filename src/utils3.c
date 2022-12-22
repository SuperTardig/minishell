/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:40:21 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/22 12:26:13 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirections3(t_vars *vars, int i)
{
	if (ft_strcmp(vars->args[i], ">>") == 0)
	{
		if (vars->redirs == -1)
			vars->redirs = i;
		if (vars->redir_fd[1] != 1)
			close(vars->redir_fd[1]);
		if (bad_access(vars, i))
			return (1);
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
	return (0);
}

int	redirections2(t_vars *vars, int i)
{
	if (ft_strcmp(vars->args[i], "<") == 0)
	{
		if (vars->redirs == -1)
			vars->redirs = i;
		if (vars->redir_fd[0] != 0)
			close(vars->redir_fd[0]);
		if (bad_access(vars, i))
			return (1);
		vars->redir_fd[0] = open(vars->args[i + 1], O_RDONLY);
		if (vars->redir_fd[0] == -1)
		{
			printf("%s: No such file or directory\n", vars->args[i + 1]);
			return (1);
		}
	}
	else if (ft_strcmp(vars->args[i], ">>") == 0
		|| ft_strcmp(vars->args[i], "<<") == 0)
		if (redirections3(vars, i))
			return (1);
	return (0);
}

int	bad_access(t_vars *vars, int i)
{
	if (access(vars->args[i + 1], F_OK) == 0)
	{
		if (access(vars->args[i + 1], W_OK) != 0)
		{
			printf("%s: Permission denied\n", vars->args[i + 1]);
			return (1);
		}
	}
	return (0);
}

int	valid_exec(t_vars *vars)
{
	if (access(vars->path, X_OK) != 0)
	{
		printf("%s: Permission denied\n", vars->args[0]);
		return (1);
	}
	return (0);
}

int	check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] == c)
		i++;
	if (i != (int) ft_strlen(str))
		return (0);
	return (1);
}
