/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:09:56 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/26 14:27:14 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*look_path(t_vars *vars, char *cmd)
{
	char	*path;
	char	*slash_path;
	char	**sep_path;
	int		i;

	i = 0;
	while (ft_strnstr(vars->env[i], "PATH=", 5) == NULL)
		++i;
	sep_path = ft_split(vars->env[i] + 5, ':');
	i = -1;
	while (sep_path[++i])
	{
		slash_path = ft_strjoin(sep_path[i], "/");
		path = ft_strjoin(slash_path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
	}
	return (NULL);
}

char	*get_cmd(t_vars *vars)
{
	int		len;
	char	*cmd;

	len = 0;
	while (vars->cmd[vars->i_cmd])
	{
		vars->i_cmd++;
		len++;
	}
	vars->i_cmd -= len;
	cmd = ft_substr(vars->cmd, vars->i_cmd, len);
	return (cmd);
}

char	**get_args(t_vars *vars, int start)
{
	char	**args;
	int		i;
	int		j;
	int		k;

	i = start;
	while (vars->piped[i] && ft_strcmp(vars->piped[i], "|") != 0)
		++i;
	i -= start;
	args = ft_calloc(i + 1, sizeof(char *));
	j = -1;
	while (++j < i)
		args[j] = ft_calloc
			(ft_strlen(vars->piped[start + j]) + 1, sizeof(char));
	j = -1;
	while (++j < i)
	{
		k = -1;
		while (++k < (int)ft_strlen(vars->piped[start + j]))
			args[j][k] = vars->piped[start + j][k];
	}
	return (args);
}

void	its_piping_time(t_vars *vars, char *path, int start)
{
	int		i;
	pid_t	pid;
	char	**args;

	args = get_args(vars, start);
	i = -1;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		execve(path, args, vars->env);
		perror(NULL);
		exit(1);
	}
	while (args[++i])
		free(args[i]);
	free(args);
	waitpid(pid, &vars->last_status, 0);
}

void	find_cmd(t_vars *vars)
{
	char	*cmd_path;

	if (vars->path_to_take == 8)
		cmd_path = ft_exec(vars, 0);
	else
		cmd_path = look_path(vars, vars->piped[0]);
	if (cmd_path == NULL)
	{
		printf("command not found: %s\n", vars->piped[0]);
		vars->last_status = errno;
		return ;
	}
	its_piping_time(vars, cmd_path, 0);
}
