/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:33:43 by bperron           #+#    #+#             */
/*   Updated: 2022/11/02 14:03:48 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*int	meta_num(char *cmd)
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

	vars->metas = ft_calloc(sizeof(char), meta_num(vars->cmd));
	i = 0;
	j = 0;
	while (vars->cmd[i])
	{
		if (ft_strchr("<>", vars->cmd[i]))
		{
			vars->is_meta = 1;
			vars->metas[j++] = vars->cmd[i];
			vars->cmd[i] = '\0';
		}
		i++;
	}
	vars->metas[j] = '\0';
}*/

void	rm_exec(t_vars *vars, int index)
{
	char	*tmp;

	tmp = ft_strdup(vars->piped[index]);
	free(vars->piped[index]);
	vars->piped[index] = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
	tmp = ft_substr(tmp, 2, ft_strlen(tmp) - 2);
	ft_strlcpy(vars->piped[index], tmp, ft_strlen(tmp) + 1);
}

void	find_the_cmd(char *cmd, t_vars *vars, int index)
{
	if (cmp(cmd, "CD") == 1)
		vars->path_to_take = 0;
	else if (cmp(cmd, "echo") == 1 || cmp(cmd, "ECHO") == 1)
		vars->path_to_take = 1;
	else if (cmp(cmd, "exit") == 1)
		vars->path_to_take = 2;
	else if (cmp(cmd, "cd") == 1)
		vars->path_to_take = 3;
	else if (cmp(cmd, "pwd") == 1 || cmp(cmd, "PWD") == 1)
		vars->path_to_take = 4;
	else if (cmp(cmd, "export") == 1)
		vars->path_to_take = 5;
	else if (cmp(cmd, "env") == 1 || cmp(cmd, "ENV") == 1)
		vars->path_to_take = 6;
	else if (cmp(cmd, "unset") == 1)
		vars->path_to_take = 7;
	else if (cmd[0] == '.' && cmd[1] == '/')
	{
		rm_exec(vars, index);
		vars->path_to_take = 8;
	}
	else
		vars->path_to_take = 9;
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
	vars->last_var = -1;
	del_spaces(vars);
	loop_var(vars, -1, 0, 0);
	check_pipe(vars);
	split_args(vars);
	check_if_pipes(vars);
	vars->row = 0;
	vars->i_cmd = 0;
	vars->i_meta = 0;
	while (vars->piped[vars->row])
	{
		find_the_cmd(vars->piped[vars->row], vars, vars->row);
		exec_cmd(vars);
		vars->row++;
	}
/* 	if (vars->is_meta == 1)
		free(vars->metas); */
}
