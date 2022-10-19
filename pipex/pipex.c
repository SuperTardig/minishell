/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/19 10:50:56 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*look_path(char *envp[], char *cmd)
{
	char	*path;
	char	*slash_path;
	char	**sep_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		++i;
	sep_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (sep_path[++i])
	{
		slash_path = ft_strjoin(sep_path[i], "/");
		path = ft_strjoin(slash_path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
	}
	ft_putstr_fd("invalid command\n", 2);
	return (NULL);
}

int	do_child2(int count)
{
	int	fd[2];
	int	pids;

	while (--count)
	{
		pids = fork();
		if (pids < 0)
			return (1);
		if (pids == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			if (count != 1)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve();
		}
	}
	return (0);
}

int	do_child(t_vars *vars, char *cmd_path)
{
	int	fd[2];
	int	pid1;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmd_path, vars->piped[0], vars->env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	return (0);
}

void	i_do_piping(t_vars *vars)
{
	char	*cmd_path;

	cmd_path = look_path(vars->env, vars->piped[0]);
	if (cmd_path == NULL)
		printf("pipe execution failed");
	if (!do_child(vars, cmd_path))
		printf("pipe execution failed");
}
