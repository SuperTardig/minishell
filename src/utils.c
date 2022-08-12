/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:40:21 by bperron           #+#    #+#             */
/*   Updated: 2022/08/12 10:45:34 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_prompt(void)
{
	//static int	first_open = 1;

	/* if (first_open == 1) //check for first time opening command prompt
	{
		printf("\e[1;1H\e[2J"); //clear screen
		first_open = 0;
	} */
	printf("\e[0;29mMinishell >"); //command line
}
