/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:30:44 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/02 13:36:29 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirections(t_vars *vars)
{
	int	i;

	i = -1;
	while (vars->args[++i])
	{
		if (ft_strcmp(vars->args[i], ">") == 0)
			;
		else if (ft_strcmp(vars->args[i], "<") == 0)
			;
		else if (ft_strcmp(vars->args[i], ">>") == 0)
			;
		else if (ft_strcmp(vars->args[i], "<<") == 0)
			;
	}
}
