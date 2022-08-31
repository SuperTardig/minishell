/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:09:52 by bperron           #+#    #+#             */
/*   Updated: 2022/08/30 13:57:50 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//sert a quitter le shell avec un exit code donner par le user ou celui de la dernier commande utiliser
//va falloir mettre les bons parametre
void	ft_exit(t_vars *vars)
{
	int	status = 0;

	printf("exit\n");
	if (check_args(vars) == 1)
	{
		
	}
	else if (check_args(vars) == 0)
		status = vars->last_status;
	else
	{
		errno = 7;
		perror("exit:");
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
			vars->env[i] = ft_strjoin(ft_strtrim(vars->env[i], "="), new);
		else if (ft_strnstr(vars->env[i], "OLDPWD", 6) != NULL)
			vars->env[i] = ft_strjoin(ft_strtrim(vars->env[i], "="), old);
	}
}

//faut encore combiner le home et pas home pour que ca prenne moins de place
void	ft_cd(t_vars *vars)
{
	int		i;
	char	*old;
	char	*new;
	//char	*path;

	i = -1;
	old = ft_calloc(sizeof(char), 1000);
	new = ft_calloc(sizeof(char), 1000);
	if (check_args(vars) >= 1)
	{
		while (++i < vars->cmd_len)
		{
			if (vars->cmd[i] == '\0')
			{
				while (vars->cmd[i] == '\0' && i < vars->cmd_len)
					i++;
				getcwd(old, 1000);
				vars->last_status = chdir(&vars->cmd[i]);
				getcwd(new, 1000);
				change_pwd(old, new, vars);
				break ;
			}
		}
	}
	else
	{
		while (vars->env[i])
		{
			if (ft_strnstr(vars->env[i], "HOME", 4) != NULL)
				(void) vars;
		}
	}
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