/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:36:56 by bperron           #+#    #+#             */
/*   Updated: 2022/11/22 09:50:02 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sighandlerc(int signum)
{
	int	pid;

	pid = getpid();
	if (pid == 0)
		exit (0);
	else
	{
		if (signum == SIGINT)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	sighush(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	return ;
}

void	signal_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandlerc);
}
