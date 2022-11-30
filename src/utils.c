/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:40:21 by bperron           #+#    #+#             */
/*   Updated: 2022/11/30 12:55:20 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmp(char *cmd, char *try)
{
	int	i;

	i = 0;
	while (cmd[i] && try[i] && cmd[i] == try[i])
		i++;
	if (cmd[i] || try[i])
		return (0);
	return (1);
}

void	free_garbage(t_vars *vars, int status)
{
	t_list	*hold;

	if (vars->cmd)
		free(vars->cmd);
	if (vars->piped)
		free_arrarr(vars->piped);
	if (vars->garbage)
	{
		hold = vars->garbage;
		while (hold != NULL)
		{
			hold = vars->garbage->next;
			free(vars->garbage->content);
			vars->garbage = hold;
		}
	}
	exit(status);
}
