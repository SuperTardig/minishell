/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:09:52 by bperron           #+#    #+#             */
/*   Updated: 2022/09/07 11:35:29 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_export(t_vars *vars)
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