/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:07:15 by bperron           #+#    #+#             */
/*   Updated: 2022/12/22 12:23:55 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_vars *vars)
{
	char	*buf;

	buf = ft_calloc(sizeof(char), 1000);
	getcwd(buf, 1000);
	if (buf[0] != '\0')
	{
		printf("%s\n", buf);
		vars->last_status = 0;
	}
	else
	{
		vars->last_status = errno;
		perror("pwd");
	}
	free(buf);
	exit(vars->last_status);
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

char	*find_path(t_vars *vars)
{
	int	i;

	i = -1;
	if (ft_argsize(vars->piped) > 1)
		return (vars->piped[vars->index + 1]);
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
		ft_fprintf(2, "cd: %s: ", vars->piped[vars->index + 1]);
		perror("");
	}
	else
		vars->last_status = 0;
}
