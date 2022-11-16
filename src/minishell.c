/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2022/11/10 14:02:37 by bperron          ###   ########.fr       */
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
		vars.env = envp;
		vars.last_status = 0;
		signal_handling();
		while (1)
		{
			vars.cmd = NULL;
			if (!ft_readline(&vars))
				return (0);
			parsing(&vars);
		}
	}
	else
		printf("Too many arguments\nUsage : ./minishell\n");
	return (0);
}
