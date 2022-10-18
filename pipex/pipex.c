/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/09 12:43:08 by bperron          ###   ########.fr       */
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

int	do_child(int count)
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
		execve();
	}
	if (do_child2(count) == 1)
		return (1);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

void	main(t_vars *vars)
{
	char	*cmd_path;

	cmd_path = look_path(vars->env, vars->piped[0]);
	if (cmd_path != NULL)
		if (do_child(argc))
			printf("pipe execution failed");
	else
		printf("pipe execution failed");
}
