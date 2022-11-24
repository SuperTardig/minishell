/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:35:48 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/23 14:49:28 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_exec(t_vars *vars, int index)
{
	char	*buf;
	char	*tmp;

	buf = ft_calloc(1000, sizeof(char));
	getcwd(buf, 1000);
	tmp = ft_strjoin(buf, "/");
	free(buf);
	ft_strlcat(tmp, vars->piped[index], 1000);
	return (tmp);
}
