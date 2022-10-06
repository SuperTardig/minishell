/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector_steve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:18:52 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/22 12:48:46 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*rm_spaces(t_vars *vars, int len, int quote_pos, int dquote_pos)
{
	char	*buffer;
	int		i;
	int		j;

	buffer = malloc(sizeof(char) * (len + 1));
	quote_pos = 0;
	dquote_pos = 0;
	i = -1;
	j = -1;
	while (++i < vars->cmd_len)
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
	return (buffer);
}

char	*search_quotes(t_vars *vars)
{
	int	i;
	int	j;
	int	quote_pos;
	int	dquote_pos;

	i = -1;
	j = 0;
	quote_pos = 0;
	dquote_pos = 0;
	while (++i < vars->cmd_len)
	{
		if (vars->cmd[i] == ' ' && quote_pos == 0 && dquote_pos == 0)
			while (vars->cmd[i++] == ' ')
				++j;
		else if (dquote_pos == 0 && quote_pos == 0 && vars->cmd[i] == '"')
			dquote_pos = 1;
		else if (quote_pos == 0 && dquote_pos == 0 && vars->cmd[i] == '\'')
			quote_pos = 1;
		else if (quote_pos == 1 && vars->cmd[i] == '\'')
			quote_pos = 0;
		else if (dquote_pos == 1 && vars->cmd[i] == '"')
			dquote_pos = 0;
	}
	return (rm_spaces(vars, i - j, quote_pos, dquote_pos));
}

void	before_tok(t_vars *vars)
{
	vars->cmd = ft_strtrim(vars->cmd, " ");
	vars->cmd_len = ft_strlen(vars->cmd);
	vars->cmd = search_quotes(vars);
}
