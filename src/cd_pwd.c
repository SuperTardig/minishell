/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:07:15 by bperron           #+#    #+#             */
/*   Updated: 2022/10/19 10:50:17 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_vars *vars)
{
	char	*buf;

	if (ft_arrsize(vars->piped) == 1)
	{
		buf = ft_calloc(sizeof(char), 1000);
		getcwd(buf, 1000);
		if (buf[0] != '\0')
			printf("%s\n", buf);
		else
		{
			vars->last_status = errno;
			perror("pwd");
		}
		free(buf);
	}
	else
	{
		vars->last_status = 7;
		errno = 7;
		ft_fprintf(2, "pwd: too many arguments\n");
	}
}

void	change_pwd(char *old, char *new, t_vars *vars)
{
	int		i;

	i = -1;
	while (vars->env[++i])
	{
		if (ft_strnstr(vars->env[i], "PWD", 3) != NULL)
			vars->env[i] = ft_strjoin(ft_substr(vars->env[i], 0, 4), new);
		else if (ft_strnstr(vars->env[i], "OLDPWD", 6) != NULL)
			vars->env[i] = ft_strjoin(ft_substr(vars->env[i], 0, 7), old);
	}
}

static	char	*find_path(t_vars *vars)
{
	int	i;

	i = -1;
	if (ft_arrsize(vars->piped) > 1)
	{
		vars->row++;
		return (vars->piped[vars->row]);
	}
	else
	{
		while (vars->env[++i])
		{
			if (ft_strnstr(vars->env[i], "HOME", 4) != NULL)
				return (&vars->env[i][5]);
		}
	}
	return (NULL);
}

void	ft_cd(t_vars *vars)
{
	char	*old;
	char	*new;

	old = ft_calloc(sizeof(char), 1000);
	new = ft_calloc(sizeof(char), 1000);
	getcwd(old, 1000);
	vars->last_status = chdir(find_path(vars));
	change_pwd(old, getcwd(new, 1000), vars);
	free(old);
	free(new);
	if (vars->last_status == -1)
	{
		ft_fprintf(2, "cd: %s: ", vars->piped[vars->row]);
		perror("");
	}
}
