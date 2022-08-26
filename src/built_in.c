/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:09:52 by bperron           #+#    #+#             */
/*   Updated: 2022/08/26 14:28:49 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//sert a quitter le shell avec un exit code donner par le user ou celui de la dernier commande utiliser
//va falloir mettre les bons parametre
void	ft_exit(t_vars *vars)
{
	(void) vars;
	printf("exit\n");
	//int	status;

	//if () regarder si un argument a ete donner
	//	status = arg;
	//else 
	//	status = last_status;
	//free_all(); va falloir la creer
	//exit (status);
	exit (0);
}

//sert a imprimer quelque chose
//va falloir mettre les bons parametre
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
//va falloir mettre les parametre
void	ft_pwd(t_vars *vars)
{
	int	i;

	i = -1;
	while (vars->env[++i])
	{
		if (ft_strnstr(vars->env[i], "PWD", 3) != NULL)
			break ;
	}
	//if ( == 1)
		printf("%s\n", &vars->env[i][4]);
	//else
	//	printf("pwd: too many arguments");
}

void	ft_cd(t_vars *vars)
{
	(void) vars;
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