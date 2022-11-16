/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:36:56 by bperron           #+#    #+#             */
/*   Updated: 2022/11/16 13:32:14 by bperron          ###   ########.fr       */
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

void	signal_handling(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_mask = SA_SIGINFO;
	sig.sa_handler = &sighandlerc;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sig, NULL);
}
