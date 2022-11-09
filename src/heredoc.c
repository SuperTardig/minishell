/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:37:49 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/09 16:28:14 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	heredoc(t_vars *vars, int i)
{
	int		fds[2];
	int		fd;
	char	*cmd;

	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(1);
	}
	fd = open("tmp.txt", O_WRONLY | O_CREAT, 0777);
	dup2(fds[1], fd);
	close(fds[1]);
	while (1)
	{
		cmd = readline("> ");
		if (ft_strcmp(cmd, vars->args[i + 1]) == 0)
			break ;
		write(fd, &cmd, ft_strlen(cmd));
	}
	return (fds[0]);
}
