/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:37:49 by fleduc            #+#    #+#             */
/*   Updated: 2022/12/22 12:34:45 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	loop_the_var(t_vars *vars, int i)
{
	while (vars->h_cmd[++i])
	{
		if (vars->h_cmd[i] == '$'
			&& ((vars->h_cmd[i + 1] >= 'a' && vars->h_cmd[i + 1] <= 'z')
				|| (vars->h_cmd[i + 1] >= 'A' && vars->h_cmd[i + 1] <= 'Z')
				|| vars->h_cmd[i + 1] == '_'))
		{
			find_the_var(vars, i + 1);
			break ;
		}
		else if (vars->h_cmd[i] == '$' && vars->h_cmd[i + 1] == '?')
		{
			ft_status(vars, -1, -1, -1);
			break ;
		}
	}
}

int	put_the_new_var(t_vars *vars, char *new, int var_place, int env_place)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (new[j])
		j++;
	while (vars->env[env_place][i] != '=')
		i++;
	i++;
	vars->last_var = var_place + i - 2;
	while (vars->env[env_place][i])
		new[j++] = vars->env[env_place][i++];
	return (j);
}

void	change_the_var(t_vars *vars, int var_place, int env_i, int len)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(vars->h_cmd) - ft_strlen_until(vars->env[env_i],
				'=') + find_var_len(vars, env_i) + 1, sizeof(char));
	if (new == NULL)
		return ;
	i = -1;
	j = -1;
	while (++i < var_place)
		new[++j] = vars->h_cmd[i];
	i += len;
	j++;
	j = put_the_new_var(vars, new, var_place, env_i);
	while (vars->h_cmd[i])
		new[j++] = vars->h_cmd[i++];
	new[j] = '\0';
	free(vars->h_cmd);
	vars->h_cmd = new;
	loop_the_var(vars, -1);
}

void	find_the_var(t_vars *vars, int i)
{
	char	*var;
	int		exist;
	int		j;

	exist = 0;
	j = 0;
	while (vars->h_cmd[i + j] && ((vars->h_cmd[i + j] >= 'a'
				&& vars->h_cmd[i + j] <= 'z') || (vars->h_cmd[i + j] >= 'A'
				&& vars->h_cmd[i + j] <= 'Z') || (vars->h_cmd[i + j] >= '0'
				&& vars->h_cmd[i + j] <= '9') || vars->h_cmd[i + j] == '_'))
		++j;
	var = ft_strjoin(ft_substr(vars->h_cmd, i, j), "=");
	j = -1;
	while (vars->env[++j])
	{
		if (ft_strnstr(vars->env[j], var, ft_strlen(var)) != NULL)
		{
			exist = 1;
			break ;
		}
	}
	if (exist == 1)
		change_the_var(vars, i - 1, j, ft_strlen(var));
	else
		ft_cutstr(vars, i - 1, i + ft_strlen(var) - 2);
}

int	heredoc(t_vars *vars, int i)
{
	int		fds[2];

	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		vars->h_cmd = readline("> ");
		if (ft_strcmp(vars->h_cmd, vars->args[i + 1]) == 0)
			break ;
		loop_the_var(vars, -1);
		ft_putendl_fd(vars->h_cmd, fds[1]);
		free(vars->h_cmd);
	}
	free(vars->h_cmd);
	close(fds[1]);
	return (fds[0]);
}
