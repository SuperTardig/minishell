/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:09:56 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/07 14:53:23 by bperron          ###   ########.fr       */
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

void	mini_pipe(t_vars *vars, char *path)
{
	int		pid;
	char	*argv[] = {path, NULL};

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		execve(path, argv, vars->env);
	waitpid(pid, NULL, 0);
} 

void	find_cmd(t_vars *vars)
{
	char	*cmd_path;
	char	*cmd;

	if (vars->cmd[vars->i_cmd] != '\0')
	{
		printf("ok\n");
		cmd = get_cmd(vars);
		cmd_path = look_path(vars, cmd);
		if (cmd_path == NULL)
			return ;
		mini_pipe(vars, cmd_path);
	}
}
