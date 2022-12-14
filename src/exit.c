/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:46:29 by bperron           #+#    #+#             */
/*   Updated: 2022/12/14 16:23:11 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
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
	if (check_arg(vars->piped[vars->index + 1]) > 19)
	{
		errno = 22;
		ft_fprintf(2, "Minishell: exit: %s: ", vars->piped[vars->index + 1]);
		perror("");
		*status = 255;
	}
	else
		*status = atoll(vars->piped[vars->index + 1]);
}

void	ft_exit(t_vars *vars)
{
	unsigned char	status;
	int				args;

	status = 0;
	printf("exit\n");
	args = ft_argsize(&vars->piped[vars->index]);
	if (args == 2)
		set_status(vars, &status);
	else if (args == 1)
		status = vars->last_status;
	else
	{
		errno = 7;
		vars->last_status = 7;
		perror("Minishell: exit");
		return ;
	}
	free_garbage(vars, status);
}
