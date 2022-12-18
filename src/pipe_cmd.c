/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/18 12:09:37 by fleduc           ###   ########.fr       */
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
		good_file(vars);
		if (vars->path_to_take != 4 && vars->path_to_take != 9)
			exec_cmd(vars);
		else
		{
			if (vars->path == NULL)
				exit(0);
			else if (vars->redir_args)
				execve(vars->path, vars->redir_args, vars->env);
			else
				execve(vars->path, vars->args, vars->env);
			perror("execve");
		}
		exit(1);
	}
	if (vars->nb_pipe != 0)
	{
		dup2(vars->fd_pipe[0], STDIN_FILENO);
		close(vars->fd_pipe[0]);
		close(vars->fd_pipe[1]);
	}
	loop_index(vars);
	if (ft_strcmp(vars->path, "bin/cat") != 0 && vars->nb_pipe == 0)
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

void	piper(t_vars *vars)
{
	while (vars->nb_pipe >= 0)
	{
		if (vars->path_to_take != 4)
			find_the_cmd(vars->piped[vars->index], vars, vars->index);
		vars->args = get_args(vars, vars->index);
		if (vars->path_to_take == 4)
		{
			vars->path = ft_exec(vars, vars->index);
			if (valid_exec(vars))
			{
				vars->nb_pipe -= 1;
				continue ;
			}
		}
		else
			vars->path = look_path(vars, vars->piped[vars->index]);
		if (cmd_not_found(vars))
		{
			vars->nb_pipe -= 1;
			continue ;
		}
		piper2(vars);
	}
}
