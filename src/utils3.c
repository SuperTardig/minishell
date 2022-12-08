/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:40:21 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/08 12:51:33 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirections3(t_vars *vars, int i)
{
	if (ft_strcmp(vars->args[i], ">>") == 0)
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

int	redirections2(t_vars *vars, int i)
{
	if (ft_strcmp(vars->args[i], "<") == 0)
	{
		if (vars->redirs == -1)
			vars->redirs = i;
		if (vars->redir_fd[0] != 0)
			close(vars->redir_fd[0]);
		vars->redir_fd[0] = open(vars->args[i + 1], O_RDONLY);
		if (vars->redir_fd[0] == -1)
		{
			printf("%s: No such file or directory\n", vars->args[i + 1]);
			return (1);
		}
	}
	else if (ft_strcmp(vars->args[i], ">>") == 0
		|| ft_strcmp(vars->args[i], "<<") == 0)
		redirections3(vars, i);
	return (0);
}
