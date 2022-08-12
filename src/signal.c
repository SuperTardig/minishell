/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:36:56 by bperron           #+#    #+#             */
/*   Updated: 2022/08/12 10:41:47 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sighandlerc(int signum, siginfo_t *s_info, void *content)
{
	(void) signum;
	(void) s_info;
	(void) content;
	cmd_prompt();
}

void	sighandler(int signum, siginfo_t *s_info, void *content)
{
	(void) signum;
	(void) s_info;
	(void) content;
	return ;
}

void	signal_handling(void)
{
	struct sigaction	sigc;
	struct sigaction	sig;

	ft_memset(&sigc, 0, sizeof(struct sigaction));
	ft_memset(&sig, 0, sizeof(struct sigaction));
	sigc.sa_sigaction = &sighandlerc;
	sig.sa_sigaction = &sighandler;
	sigaction(SIGINT, &sigc, NULL);
	sigaction(SIGABRT, &sig, NULL);
}
