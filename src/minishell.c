/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2022/12/22 12:39:29 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_readline(t_vars *vars)
{
	if (vars->cmd)
	{
		free(vars->cmd);
		vars->cmd = NULL;
	}
	vars->cmd = readline("Minishell > ");
	if (vars->cmd == NULL)
		return (0);
	if (vars->cmd && *(vars->cmd))
		add_history(vars->cmd);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void) argv;
	if (argc == 1)
	{
		vars.is_malloc = 0;
		vars.env = envp;
		vars.last_status = 0;
		while (1)
		{
			signal_handling();
			vars.cmd = NULL;
			vars.piped = NULL;
			if (!ft_readline(&vars))
				free_garbage(&vars, 0);
			signal(SIGQUIT, sighush);
			signal(SIGINT, sighush);
			parsing(&vars);
		}
	}
	else
		printf("Too many arguments\nUsage : ./minishell\n");
	return (0);
}
