/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/02 13:59:28 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	do_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

void	dumpling(t_vars *vars, pid_t pid)
{
	if (pid == 0)
	{
		dup2(vars->fd_pipe[1], STDOUT_FILENO);
		close(vars->fd_pipe[0]);
		close(vars->fd_pipe[1]);
	}
}

void	do_execve(t_vars *vars, pid_t pid)
{
	if (pid == 0)
	{
		execve(vars->path, vars->args, vars->env);
		perror("execve");
		exit(1);
	}
	if (vars->nb_pipe != 0)
	{
		dup2(vars->fd_pipe[0], STDIN_FILENO);
		close(vars->fd_pipe[0]);
		close(vars->fd_pipe[1]);
	}
	while (vars->piped[vars->index]
		&& ft_strcmp(vars->piped[vars->index], "|") != 0)
			++(vars->index);
	while (vars->piped[vars->index]
		&& ft_strcmp(vars->piped[vars->index], "|") == 0)
			++(vars->index);
	waitpid(pid, &vars->last_status, 0);
}

void	do_pipe(t_vars *vars)
{
	if (pipe(vars->fd_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	piper(t_vars *vars, pid_t pid2)
{
	pid_t	pid;

	while (pid2 == 0 && vars->nb_pipe >= 0)
	{
		vars->args = get_args(vars, vars->index);
		redirections(vars);
		vars->path = look_path(vars, vars->piped[vars->index]);
		if (cmd_not_found(vars))
			continue ;
		if (vars->nb_pipe != 0)
			do_pipe(vars);
		pid = do_fork();
		if (vars->nb_pipe != 0)
			dumpling(vars, pid);
		do_execve(vars, pid);
		free_pipe_args(vars);
		--(vars->nb_pipe);
	}
}