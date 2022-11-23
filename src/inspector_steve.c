/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector_steve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:18:52 by fleduc            #+#    #+#             */
/*   Updated: 2022/11/23 08:36:21 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	rm_spaces(t_vars *vars, int len, int quote_pos, int dquote_pos)
{
	char	*buffer;
	int		i;
	int		j;

	buffer = ft_calloc(sizeof(char), (len));
	i = -1;
	j = -1;
	while (vars->cmd[++i])
	{
		if (vars->cmd[i] == ' ' && quote_pos == 0 && dquote_pos == 0)
			while (vars->cmd[i + 1] == ' ')
				++i;
		else if (dquote_pos == 0 && quote_pos == 0 && vars->cmd[i] == '"')
			dquote_pos = 1;
		else if (quote_pos == 0 && dquote_pos == 0 && vars->cmd[i] == '\'')
			quote_pos = 1;
		else if (quote_pos == 1 && vars->cmd[i] == '\'')
			quote_pos = 0;
		else if (dquote_pos == 1 && vars->cmd[i] == '"')
			dquote_pos = 0;
		buffer[++j] = vars->cmd[i];
	}
	free(vars->cmd);
	vars->cmd = buffer;
}

int	quotes_error(int quote, int dquote)
{
	if (quote % 2 == 1 || dquote % 2 == 1)
	{
		printf("unclosed quotes or double quotes\n");
		return (1);
	}
	return (0);
}

int	search_quotes(t_vars *vars, int quote_pos, int dquote_pos, int i)
{
	int	j;

	j = 0;
	while (vars->cmd[++i])
	{
		if (vars->cmd[i] == ' ' && quote_pos % 2 == 0 && dquote_pos % 2 == 0)
		{
			while (vars->cmd[i] == ' ')
			{
				++i;
				++j;
			}
		}
		if (quote_pos % 2 == 0 && vars->cmd[i] == '"')
			dquote_pos++;
		else if (dquote_pos % 2 == 0 && vars->cmd[i] == '\'')
			quote_pos++;
	}
	if (quotes_error(quote_pos, dquote_pos))
		return (1);
	rm_spaces(vars, i - j + 1, 0, 0);
	return (0);
}

int	del_spaces(t_vars *vars)
{
	char	*hold;

	hold = ft_strtrim(vars->cmd, " ");
	free(vars->cmd);
	vars->cmd = hold;
	if (search_quotes(vars, 0, 0, -1))
		return (1);
	return (0);
}
