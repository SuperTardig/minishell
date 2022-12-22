/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:10:38 by bperron           #+#    #+#             */
/*   Updated: 2022/12/22 12:29:09 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_size(char *str, int i, int doubles, int singles)
{
	int	size;

	size = 0;
	if ((str[i] == '>' || str[i] == '<'))
	{
		while ((str[i] == '>' || str[i] == '<') && str[i++])
			size++;
	}
	else
	{
		while (str[i])
		{
			if (str[i] == '"' && singles % 2 == 0)
				doubles++;
			else if (str[i] == '\'' && doubles % 2 == 0)
				singles++;
			if ((str[i] == '>' || str[i] == '<')
				&& singles % 2 == 0 && doubles % 2 == 0)
				break ;
			size++;
			i++;
		}
	}
	return (size);
}

char	*new_str(t_vars *vars, int *j, int *i)
{
	char	*str;
	int		k;
	int		size;

	k = 0;
	size = find_size(&vars->piped[*j][*i], 0, 0, 0);
	str = ft_calloc(size + 1, sizeof(char));
	while (size-- > 0)
	{
		str[k++] = vars->piped[*j][*i];
		*i += 1;
	}
	return (str);
}

char	*help_redir(t_vars *vars, int *j, int *k)
{
	char	*hold;

	hold = new_str(vars, j, k);
	if (vars->piped[*j])
	{
		if (!vars->piped[*j][*k])
		{
			*k = 0;
			*j += 1;
		}
	}
	return (hold);
}

void	check_redir(t_vars *vars)
{
	char	**new_piped;
	int		nb_redir;
	int		i;
	int		j;
	int		k;

	nb_redir = count_redir(vars, 0, 0);
	if (nb_redir >= 2)
	{
		new_piped = ft_calloc(nb_redir + 1, sizeof(char *));
		i = -1;
		j = 0;
		k = 0;
		while (++i <= nb_redir)
		{
			if (i == nb_redir)
				new_piped[i] = NULL;
			else
				new_piped[i] = help_redir(vars, &j, &k);
		}
		free_arrarr(vars->piped);
		vars->piped = new_piped;
	}
}
