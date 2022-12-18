/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:33:43 by bperron           #+#    #+#             */
/*   Updated: 2022/12/18 14:29:29 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec(char *cmd)
{
	char	*buf;
	char	*tmp;

	buf = ft_calloc(sizeof(char), 1000);
	getcwd(buf, 1000);
	ft_strlcat(buf, "/", ft_strlen(buf) + 2);
	tmp = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
	ft_strlcat(buf, tmp, ft_strlen(buf) + ft_strlen(tmp) + 1);
	free(tmp);
	if (access(buf, F_OK | X_OK) == 0)
	{
		free(buf);
		return (1);
	}
	free(buf);
	return (0);
}

void	find_the_cmd(char *cmd, t_vars *vars)
{
	if (cmp(cmd, "CD") == 1)
		vars->path_to_take = 0;
	else if (cmp(cmd, "exit") == 1)
		vars->path_to_take = 1;
	else if (cmp(cmd, "cd") == 1)
		vars->path_to_take = 2;
	else if (cmp(cmd, "unset") == 1)
		vars->path_to_take = 3;
	else if (cmp(cmd, "pwd") == 1 || cmp(cmd, "PWD") == 1)
		vars->path_to_take = 5;
	else if (cmp(cmd, "export") == 1)
		vars->path_to_take = 6;
	else if (cmp(cmd, "env") == 1 || cmp(cmd, "ENV") == 1)
		vars->path_to_take = 7;
	else if (cmp(cmd, "echo") == 1 || cmp(cmd, "ECHO") == 1)
		vars->path_to_take = 8;
	else
		vars->path_to_take = 9;
}

void	exec_cmd(t_vars *vars)
{
	if (vars->path_to_take == 1)
		ft_exit(vars);
	else if (vars->path_to_take == 2)
		ft_cd(vars);
	else if (vars->path_to_take == 3)
		ft_unset(vars);
	else if (vars->path_to_take == 5)
		ft_pwd(vars);
	else if (vars->path_to_take == 6)
		ft_export(vars);
	else if (vars->path_to_take == 7)
		ft_env(vars);
	else if (vars->path_to_take == 8)
		ft_echo(vars);
}

void	del_spaces2(t_vars *vars)
{
	char	**new;
	int		i;

	i = -1;
	new = ft_calloc(ft_arrsize(vars->piped) + 1, sizeof(char *));
	while (vars->piped[++i])
		new[i] = ft_strtrim(vars->piped[i], " ");
	free_arrarr(vars->piped);
	vars->piped = new;
}

void	parsing(t_vars *vars)
{
	if (!vars->cmd[0])
		return ;
	vars->last_var = -1;
	vars->index = 0;
	if (del_spaces(vars))
		return ;
	loop_var(vars, -1, 0, 0);
	check_pipe(vars, 0, 0);
	check_redir(vars);
	del_spaces2(vars);
	split_args(vars);
	check_if_pipes(vars);
	free_arrarr(vars->piped);
	free(vars->cmd);
}
