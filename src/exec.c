/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:35:48 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/26 13:00:13 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_exec(t_vars *vars, int index)
{
	char	*buf;

	buf = ft_calloc(1000, sizeof(char));
	getcwd(buf, 1000);
	buf = ft_strjoin(buf, "/");
	ft_strlcat(buf, vars->piped[index], 1000);
	return (buf);
}
