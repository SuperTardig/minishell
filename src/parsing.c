/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:33:43 by bperron           #+#    #+#             */
/*   Updated: 2022/10/04 13:43:23 by fleduc           ###   ########.fr       */
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
			vars->is_meta = 1;
			vars->metas[j++] = vars->cmd[i];
			vars->cmd[i] = '\0';
		}
		i++;
	}
	vars->metas[j] = '\0';
}

/*static	void	find_path(t_vars *vars)
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
}*/

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
	else// cest ca qui fait chier le ctrl d
		find_cmd(vars);
}

void	parsing(t_vars *vars)
{
	vars->last_var = -1;
	del_spaces(vars);
	loop_var(vars, -1, 0, 0);
	check_pipe(vars);
	/*vars->i_cmd = 0;
	vars->i_meta = 0;
	while (vars->i_cmd <= vars->cmd_len)
	{
		find_path(vars);
		exec_cmd(vars);
		while (vars->cmd[vars->i_cmd])
			vars->i_cmd++;
		vars->i_cmd++;
	}
	if (vars->is_meta == 1)
		free(vars->metas);
	*/
}
