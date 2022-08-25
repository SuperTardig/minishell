/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2022/08/25 11:22:01 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parsing(t_vars *vars)
{
	ft_strtok(vars);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void) argv;
	(void) envp;
	if (argc == 1)
	{
		while (1)
		{
			signal_handling();
			vars.cmd = readline("minishell > ");
			if (vars.cmd == NULL)
				return (0);
			parsing(&vars);
			printf("%d%s%s\n", vars.cmd_len, vars.metas, vars.cmd);
		}
	}
	else
		printf("Too many arguments\nUsage : ./minishell\n");
	return (0);
}
