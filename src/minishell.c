/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2022/08/09 13:13:07 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_prompt(void)
{
	static int	first_open = 1;

	if (first_open == 1) //check for first time opening command prompt
	{
		printf("\e[1;1H\e[2J"); //clear screen
		first_open = 0;
	}
	printf("\e[0;29mMinishell >"); //command line
}

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

int	main(void)
{
	signal_handling();
	cmd_prompt();
	sleep(10);
	//wait_cmd();
}