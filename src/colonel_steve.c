/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colonel_steve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:10:17 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/23 11:18:37 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_basic_cmd(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->metas[i])
	{
		if (vars->metas[i] != '-' || vars->metas[i] != '$'
			|| vars->metas[i] != ' ')
			return (1);
		++i;
	}
	return (0);
}

void	count_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	vars->parse.pipes = 0;
	while (vars->metas[i])
	{
		if (vars->metas[i] == '|')
			++vars->parse.pipes;
		++i;
	}
}

void	check_redirs(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->metas[i] == '$' || vars->metas[i] == ' '
		|| vars->metas[i] == '-')
	{
		if (vars->metas[i - 1] == ' ' && vars->metas[i] == '<'
			&& vars->metas[i + 1] == '<' && vars->metas[i + 2] == ' ')
			vars->parse.red = "<<";
		else if (vars->metas[i - 1] == ' ' && vars->metas[i] == '>'
			&& vars->metas[i + 1] == '>' && vars->metas[i + 2] == ' ')
			vars->parse.red = ">>";
		else if (vars->metas[i - 1] == ' ' && vars->metas[i] == '>'
			&& vars->metas[i + 1] == ' ')
			vars->parse.red = ">";
		else if (vars->metas[i - 1] == ' ' && vars->metas[i] == '<'
			&& vars->metas[i + 1] == ' ')
			vars->parse.red = "<";
		else
			vars->parse.red = NULL;
		++i;
	}
}
