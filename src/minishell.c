/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2022/08/08 15:03:38 by fleduc           ###   ########.fr       */
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

int	main(void)
{
	cmd_prompt();
	//wait_cmd();
}
