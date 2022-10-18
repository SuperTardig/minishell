/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:30:24 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/09 12:43:08 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    check_if_pipe(t_vars *vars)
{
    if (vars->nb_pipe == 0)
    {
        find_path(vars->piped[0], vars);
        exec_cmd(vars);
    }
    else
    {
        while (--vars->nb_pipe > 0)
        {
            
        }
    }
}