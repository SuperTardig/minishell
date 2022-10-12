/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:09:56 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/12 10:23:52 by bperron          ###   ########.fr       */
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

int	cmd_len(t_vars *vars, int i)
{
	int	len;

	len = 0;
	if (vars->cmd[i] == '\0' && vars->cmd[i + 1] != '\0')
	{
		++len;
		++i;
	}
	while (vars->cmd[i] != '\0')
	{
		++len;
		++i;
	}
	return (len);
}

/* char	**get_args(t_vars *vars, int len)
{
	int		nb_args;
	char	**args;
	int		i;
	int		j;
	int		k;

	nb_args = check_args(vars);
	args = ft_calloc(nb_args + 1, sizeof(char *));
	i = 0;
	k = -1;
	while (i < vars->cmd_len)
	{
		j = -1;
		len = cmd_len(vars, i);
		args[++j] = ft_calloc(len + 1, sizeof(char));
		args[j] = ft_substr(vars->cmd, i, len);
		i += len;
		while (vars->cmd[i] == '\0' && vars->metas[++k] != '-')
			++i;
	}
	 return (args);
}*/

/* void	mini_pipe(t_vars *vars, char *path)
{
	int		pid;
	int		len;
	char	**args;

	len = 0;
	args = get_args(vars, len);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (execve(path, args, vars->env) == -1)
			perror("Could not execute execve\n");
	}
	waitpid(pid, NULL, 0);
} */

/* void	find_cmd(t_vars *vars)
{
	char	*cmd_path;
	char	*cmd;

	printf("%s\n", vars->cmd);
	if (vars->cmd[vars->i_cmd] != '\0')
	{
		cmd = get_cmd(vars);
		cmd_path = look_path(vars, cmd);
		if (cmd_path == NULL)
			return ;
		mini_pipe(vars, cmd_path);
	}
} */
