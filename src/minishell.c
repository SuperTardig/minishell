/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2022/08/12 10:51:27 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parsing(char *cmd)
{
	(void) cmd;
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	(void) argv;
	(void) envp;
	if (argc == 1)
	{
		while (argc == 1)
		{
			signal_handling();
			cmd_prompt();
			cmd = readline(NULL);
			if (cmd == NULL)
				return (0);
			//parsing(cmd);
		}
	}
	else
		perror("Too many arguments\nUsage : ./minishell\nError code ");
	return (0);
}
