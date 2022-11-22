/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:37:49 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/22 09:22:39 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	heredoc(t_vars *vars, int i)
{
	int		fds[2];
	char	*cmd;

	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		cmd = readline("> ");
		if (ft_strcmp(cmd, vars->args[i + 1]) == 0)
			break ;
		ft_putendl_fd(cmd, fds[1]);
		free(cmd);
	}
	free(cmd);
	close(fds[1]);
	return (fds[0]);
}
