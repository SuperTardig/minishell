/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:33:43 by bperron           #+#    #+#             */
/*   Updated: 2022/08/25 14:26:55 by bperron          ###   ########.fr       */
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
		if (ft_strchr(";&| ()<>-", (int) cmd[i]))
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
		if (ft_strchr(";&| ()<>-", vars->cmd[i]))
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

void	find_path(t_vars *vars)
{
	int	i;

	i = 0;
	while (i <= vars->cmd_len)
	{
		if (cmp(&vars->cmd[i], "echo") == 1)
			vars->path_to_take = 1;
		else if (cmp(&vars->cmd[i], "exit") == 1)
			vars->path_to_take = 2;
		else if (cmp(&vars->cmd[i], "cd") == 1)
			vars->path_to_take = 3;
		else if (cmp(&vars->cmd[i], "pwd") == 1)
			vars->path_to_take = 4;
		else if (cmp(&vars->cmd[i], "export") == 1)
			vars->path_to_take = 5;
		else if (cmp(&vars->cmd[i], "env") == 1)
			vars->path_to_take = 6;
		else if (cmp(&vars->cmd[i], "unset") == 1)
			vars->path_to_take = 7;
		else
			vars->path_to_take = 8;
		while (vars->cmd[i])
			i++;
		i++;
	}
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
	int	i;

	ft_strtok(vars);
	i = 0;
	while (i <= vars->cmd_len)
	{
		find_path(vars);
		printf("%d\n", vars->path_to_take);
		exec_cmd(vars);
		while (vars->cmd[i])
			i++;
		i++;
	}
}