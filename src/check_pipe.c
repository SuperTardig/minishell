/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:29:09 by bperron           #+#    #+#             */
/*   Updated: 2022/10/04 10:07:38 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void check_pipe(t_vars *vars)
{
	int	i;
	int nb_pipe;

	i = -1;
	nb_pipe = 0;
	while (vars->cmd[++i])
		if (vars->cmd[i] == '|')
			nb_pipe++;
	if (nb_pipe == 0)
		return ;
	vars->piped = ft_calloc(sizeof(char *), nb_pipe + 2);
	i = 0;
	while (nb_pipe-- >= 0)
	{
		vars->piped[i++] = ft_substr(vars->cmd, 0, ft_strlen_until(vars->cmd, '|'));
		while (*vars->cmd != '|')
			vars->cmd++;
		vars->cmd++;
		while (*vars->cmd == ' ')
			vars->cmd++;
	}
	vars->piped[i] = NULL;
}

int find_var_len(t_vars *vars, int env_place)
{
	char *hold;
	
	hold = vars->env[env_place];
	while (*hold != '=')
		hold++;
	hold++;
	return (ft_strlen(hold));
}

void	change_var(t_vars *vars, int var_place, int env_place, int len)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	new = ft_calloc(ft_strlen(vars->cmd) - ft_strlen_until(vars->env[env_place], '=') + find_var_len(vars, env_place) + 1, sizeof(char));
	if (new == NULL)
		return ;
	i = -1;
	j = -1;
	while (++i < var_place)
		new[++j] = vars->cmd[i];
	i += len;
	j++;
	k = 0;
	while (vars->env[env_place][k] != '=')
		k++;
	k++;
	vars->last_var = var_place + k - 2;
	while (vars->env[env_place][k])
		new[j++] = vars->env[env_place][k++];
	while (vars->cmd[i])
		new[j++] = vars->cmd[i++];
	new[j] = '\0';
	free(vars->cmd);
	vars->cmd = new;
	loop_var(vars);
}

void    find_var(t_vars *vars, int i)
{
	char    *var;
	int     exist;
	int     j;
	
	exist = 0;
	j = 0;
	while (vars->cmd[i + j] && ((vars->cmd[i + j] >= 'a'
				&& vars->cmd[i + j] <= 'z') || (vars->cmd[i + j] >= 'A'
				&& vars->cmd[i + j] <= 'Z') || (vars->cmd[i + j] >= '0'
				&& vars->cmd[i + j] <= '9') || vars->cmd[i + j] == '_'))
		++j;
	var = ft_strjoin(ft_substr(vars->cmd, i, j), "=");
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
		change_var(vars, i - 1, j, ft_strlen(var));
}

void    loop_var(t_vars *vars)
{
	int d_quotes;
	int quotes;
	int i;
	
	i = -1;
	d_quotes = 0;
	quotes = 0;
	while (vars->cmd[++i])
	{
		if (vars->cmd[i] == '"' && quotes == 0)
			d_quotes = 1;
		else if (vars->cmd[i] == '\'' && d_quotes == 0)
			quotes = 1;
		else if (vars->cmd[i] == '"' && d_quotes == 1)
			d_quotes = 0;
		else if (vars->cmd[i] == '\'' && quotes == 1)
			quotes = 0;
		if (vars->cmd[i] == '$' && quotes != 1
			&& ((vars->cmd[i + 1] >= 'a' && vars->cmd[i + 1] <= 'z')
				|| (vars->cmd[i + 1] >= 'A' && vars->cmd[i + 1] <= 'Z')
				|| vars->cmd[i + 1] == '_') && i > vars->last_var)
		{
			find_var(vars, i + 1);
			break ;
		}
	}
}
