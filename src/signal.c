/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:36:56 by bperron           #+#    #+#             */
/*   Updated: 2022/11/17 16:01:43 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sighandlerc(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handling(void)
{
	struct sigaction	sig;

//ft_memset(&sig, 0, sizeof(sig));
	sig.sa_mask = SA_SIGINFO;
//sig.__sigaction_u.__sa_handler = SIG_IGN;
	sig.sa_handler = &sighandlerc;
	sigaction(SIGQUIT, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
}
