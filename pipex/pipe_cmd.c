/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/26 16:19:57 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	piper(t_vars *vars, int fd_in);

void	last_cmd(t_vars *vars, int fd_in, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork2");
		exit(1);
	}
	else if (pid == 0)
	{
		if (fd_in != -1)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		execve(vars->path, args, vars->env);
		perror("execve");
		exit(1);
	}
	waitpid(pid, &vars->last_status, 0);
}

void	all_cmd(t_vars *vars, int fd_in, char **args)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork1");
		exit(1);
	}
	else if (pid == 0)
	{
		if (fd_in != -1)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		execve(vars->path, args, vars->env);
		perror("execve");
		exit(1);
	}
	while (vars->piped[vars->index]
		&& ft_strcmp(vars->piped[vars->index], "|") != 0)
			++(vars->index);
	while (vars->piped[vars->index]
		&& ft_strcmp(vars->piped[vars->index], "|") == 0)
			++(vars->index);
	piper(vars, fds[0]);
	waitpid(pid, &vars->last_status, 0);
}

void	piper(t_vars *vars, int fd_in)
{
	int		i;
	char	**args;

	args = get_args(vars, vars->index);
	vars->path = look_path(vars, vars->piped[vars->index]);
	if (vars->path == NULL)
	{
		printf("command not found: %s\n", vars->piped[vars->index]);
		vars->last_status = errno;
		return ;
	}
	if (vars->nb_pipe == 0)
	{
		last_cmd(vars, fd_in, args);
	}
	else
	{
		--(vars->nb_pipe);
		all_cmd(vars, fd_in, args);
	}
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}
