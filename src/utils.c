/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:40:21 by bperron           #+#    #+#             */
/*   Updated: 2022/11/02 13:15:43 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen_until(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	cmp(char *cmd, char *try)
{
	int	i;

	i = 0;
	while (cmd[i] && try[i] && cmd[i] == try[i])
		i++;
	if (cmd[i] || try[i])
		return (0);
	return (1);
}
