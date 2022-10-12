/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:46:29 by bperron           #+#    #+#             */
/*   Updated: 2022/10/12 10:26:40 by bperron          ###   ########.fr       */
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

void	set_status(t_vars *vars, unsigned char *status)
{
	//go_to_next(vars);
	if (check_arg(vars) > 19)
	{
		errno = 22;
		ft_fprintf(2, "MiniShit: exit: %s: ", vars->cmd);
		perror("");
		*status = 255;
	}
	else
		*status = atoll(vars->cmd);
}

void	ft_exit(t_vars *vars)
{
	unsigned char	status;
	int				args;

	status = 0;
	printf("exit\n");
//	args = check_args(vars);
args =0;
	if (args == 1)
		set_status(vars, &status);
	else if (args == 0)
		status = vars->last_status;
	else
	{
		errno = 7;
		vars->last_status = 7;
		perror("MiniShit: exit");
		return ;
	}
//	free(vars->metas);
	exit (status);
}
