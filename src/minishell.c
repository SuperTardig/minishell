/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2022/09/22 13:49:43 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void) argv;
	if (argc == 1)
	{
		vars.env = envp;
		while (1)
		{
			signal_handling();
			vars.cmd = readline("MiniShit > ");
			add_history(vars.cmd);
			if (vars.cmd == NULL)
				return (0);
			//vars.cmd_len = ft_strlen(vars.cmd); //to remove
			//ft_strtok(&vars);
			parsing(&vars);
		}
	}
	else
		printf("Too many arguments\nUsage : ./minishell\n");
	return (0);
}
