/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:29:09 by bperron           #+#    #+#             */
/*   Updated: 2022/10/04 11:35:55 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_pipe(t_vars *vars)
{
	int	i;
	int	nb_pipe;

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
		vars->piped[i++] = ft_substr(vars->cmd, 0,
				ft_strlen_until(vars->cmd, '|'));
		while (*vars->cmd != '|')
			vars->cmd++;
		vars->cmd++;
		while (*vars->cmd == ' ')
			vars->cmd++;
	}
	vars->piped[i] = NULL;
}


