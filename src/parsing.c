/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:33:43 by bperron           #+#    #+#             */
/*   Updated: 2022/09/20 12:43:17 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	meta_num(char *cmd)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (cmd[++i])
	{
		if (ft_strchr("$&| ()<>-'\"", (int) cmd[i]))
			num++;
	}
	return (num);
}

void	ft_strtok(t_vars *vars)
{
	int		i;
	int		j;

	vars->cmd_len = ft_strlen(vars->cmd);
	vars->metas = ft_calloc(sizeof(char), meta_num(vars->cmd));
	i = 0;
	j = 0;
	while (vars->cmd[i])
	{
		if (ft_strchr("$&| ()<>'\"", vars->cmd[i]))
		{
			vars->metas[j++] = vars->cmd[i];
			vars->cmd[i] = '\0';
		}
		i++;
	}
	vars->metas[j] = '\0';
}

int	cmp(char *cmd, char *try)
{
	int	i;

	i = 0;
	while (cmd[i] && try[i] && cmd[i] == try[i])
		i++;
	if (cmd[i] || try[i])
		return (0);
	return (1);
}

static	void	find_path(t_vars *vars)
{
	if (cmp(&vars->cmd[vars->i_cmd], "CD") == 1)
		vars->path_to_take = 0;
	else if (cmp(&vars->cmd[vars->i_cmd], "echo") == 1
		|| cmp(&vars->cmd[vars->i_cmd], "ECHO") == 1)
		vars->path_to_take = 1;
	else if (cmp(&vars->cmd[vars->i_cmd], "exit") == 1)
		vars->path_to_take = 2;
	else if (cmp(&vars->cmd[vars->i_cmd], "cd") == 1)
		vars->path_to_take = 3;
	else if (cmp(&vars->cmd[vars->i_cmd], "pwd") == 1
		|| cmp(&vars->cmd[vars->i_cmd], "PWD") == 1)
		vars->path_to_take = 4;
	else if (cmp(&vars->cmd[vars->i_cmd], "export") == 1)
		vars->path_to_take = 5;
	else if (cmp(&vars->cmd[vars->i_cmd], "env") == 1
		|| cmp(&vars->cmd[vars->i_cmd], "ENV") == 1)
		vars->path_to_take = 6;
	else if (cmp(&vars->cmd[vars->i_cmd], "unset") == 1)
		vars->path_to_take = 7;
	else
		vars->path_to_take = 8;
}

void	exec_cmd(t_vars *vars)
{
	if (vars->path_to_take == 1)
		ft_echo(vars);
	else if (vars->path_to_take == 2)
		ft_exit(vars);
	else if (vars->path_to_take == 3)
		ft_cd(vars);
	else if (vars->path_to_take == 4)
		ft_pwd(vars);
	else if (vars->path_to_take == 5)
		ft_export(vars);
	else if (vars->path_to_take == 6)
		ft_env(vars);
	else if (vars->path_to_take == 7)
		ft_unset(vars);
	else
		find_cmd(vars);
}

void	parsing(t_vars *vars)
{
	ft_strtok(vars);
	vars->i_cmd = 0;
	vars->i_meta = 0;
	while (vars->i_cmd <= vars->cmd_len)
	{
		find_path(vars);
		exec_cmd(vars);
		while (vars->cmd[vars->i_cmd])
			vars->i_cmd++;
		vars->i_cmd++;
	}
}
