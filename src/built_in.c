/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:09:52 by bperron           #+#    #+#             */
/*   Updated: 2022/09/01 11:35:06 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_arg(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->cmd[i])
	{
		if (ft_isdigit(vars->cmd[i]) == 0)
			return (255);
		i++;
	}
	if (i > 19)
		return (20);
	else
		return (i);
}

void	go_to_next(t_vars *vars)
{
	while (vars->i_cmd < vars->cmd_len && vars->cmd[0])
	{
		vars->cmd++;
		vars->i_cmd++;
	}
	while (vars->i_cmd < vars->cmd_len && vars->cmd[0] == '\0')
	{
		if (vars->cmd[0] == '\0')
			vars->i_meta++;
		vars->i_cmd++;
		vars->cmd++;
	}
}

void	set_status(t_vars *vars, unsigned char *status)
{
	go_to_next(vars);
	if (check_arg(vars) > 19)
	{
		errno = 22;
		perror("MiniShit: exit");
		*status = 255;
	}
	else
		*status = atoll(vars->cmd);
}

//sert a quitter le shell avec un exit code donner par le user ou celui de la dernier commande utiliser
//faut creer un fprintf pour pouvoir ecrire sur stderror
void	ft_exit(t_vars *vars)
{
	unsigned char	status;
	int				args;

	status = 0;
	printf("exit\n");
	args = check_args(vars);
	if (args == 1)
		set_status(vars, &status);
	else if (args == 0)
		status = vars->last_status;
	else
	{
		errno = 7;
		perror("MiniShit: exit");
		return ;
	}
	free(vars->metas);
	exit (status);
}

//sert a imprimer quelque chose
//va falloircheck pour les flags multiples et pour les variable bash
void	ft_echo(t_vars *vars)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	while (i < 4)
		i++;
	vars->i_meta++;
	if (vars->metas[vars->i_meta] == '-')
	{
		flags = 1;
		i += 4;
	}
	while (i <= vars->cmd_len)
		if (vars->cmd[i++])
			break ;
	i--;
	if (flags == 0)
		printf ("%s\n", &vars->cmd[i]);
	else
		printf("%s", &vars->cmd[i]);
}

//sert a print le working directory
void	ft_pwd(t_vars *vars)
{
	char	*buf;

	buf = ft_calloc(sizeof(char), 1000);
	if (check_args(vars) == 0)
	{
		getcwd(buf, 1000);
		if (buf[0] != '\0')
			printf("%s\n", buf);
		else
		{
			vars->last_status = errno;
			perror("pwd: ");
		}
	}
	free(buf);
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
	if (check_args(vars) >= 1)
	{
		while (++i < vars->cmd_len)
		{
			if (vars->cmd[i] == '\0')
			{
				while (vars->cmd[i] == '\0' && i < vars->cmd_len)
					i++;
				return (&vars->cmd[i]);
			}
		}
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

//faut encore combiner le home et pas home pour que ca prenne moins de place
void	ft_cd(t_vars *vars)
{
	char	*old;
	char	*new;
	char	*path;

	old = ft_calloc(sizeof(char), 1000);
	new = ft_calloc(sizeof(char), 1000);
	path = find_path(vars);
	getcwd(old, 1000);
	vars->last_status = chdir(path);
	getcwd(new, 1000);
	change_pwd(old, new, vars);
	free(old);
	free(new);
	if (vars->last_status == -1)
		perror("cd: ");
}

void	ft_export(t_vars *vars)
{
	(void) vars;
}

void	find_cmd(t_vars *vars)
{
	(void) vars;
}

void	ft_env(t_vars *vars)
{
	int	i;

	i = -1;
	while (vars->env[++i])
		printf("%s\n", vars->env[i]);
}

void	ft_unset(t_vars *vars)
{
	(void) vars;
}