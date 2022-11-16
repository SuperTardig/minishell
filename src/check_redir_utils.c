/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:34:43 by bperron           #+#    #+#             */
/*   Updated: 2022/11/16 11:10:27 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_count(char *str, int *j, int *singles, int *doubles)
{
	if (str[*j] == '"' && *singles % 2 == 0)
		*doubles += 1;
	else if (str[*j] == '\'' && *doubles % 2 == 0)
		*singles += 1;
	if ((str[*j] == '>' || str[*j] == '<')
		&& *singles % 2 == 0 && *doubles % 2 == 0)
	{
		while ((str[*j] == '>' || str[*j] == '<') && str[*j])
			*j += 1;
		return (1);
	}
	*j += 1;
	return (0);
}

int	count_redir(t_vars *vars, int singles, int doubles)
{
	int	nb_redir;
	int	i;
	int	j;

	i = 0;
	nb_redir = 0;
	while (vars->piped[i])
	{
		j = 0;
		while (vars->piped[i][j])
			nb_redir += redir_count(vars->piped[i], &j, &singles, &doubles);
		i++;
		nb_redir++;
	}
	return (nb_redir);
}
