/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2022/10/04 08:22:44 by bperron          ###   ########.fr       */
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
		signal_handling();
		while (1)
		{
			vars.cmd = NULL;
			vars.cmd = readline("MiniShit > ");
			ft_substr(vars.cmd, 0, 2);
			if (vars.cmd == NULL)
				return (0);
			add_history(vars.cmd);
			parsing(&vars);
			free (vars.cmd);
		}
	}
	else
		printf("Too many arguments\nUsage : ./minishell\n");
	return (0);
}
