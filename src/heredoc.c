/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:37:49 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/09 16:10:04 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	heredoc(t_vars *vars, int i)
{
	int		fd;
	char	*cmd;

	while (1)
	{
		cmd = readline("> ");
		if (ft_strcmp(cmd, vars->args[i + 1]) == 0)
			break ;
	}
	fd = 1;
	return (fd);
}
