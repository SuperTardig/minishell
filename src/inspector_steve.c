/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector_steve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:18:52 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/06 13:28:02 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	rm_spaces(t_vars *vars, int len, int quote_pos, int dquote_pos)
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
	vars->cmd = buffer;
	vars->cmd[j + 1] = '\0';
	free(buffer);
}

void	quotes_error(int quote, int dquote)
{
	if (quote == 1 || dquote == 1)
	{
		printf("unclosed quotes or double quotes\n");
		exit(1);
	}
}

void	search_quotes(t_vars *vars, int quote_pos, int dquote_pos, int i)
{
	int	j;

	j = 0;
	while (vars->cmd[++i])
	{
		if (vars->cmd[i] == ' ' && quote_pos == 0 && dquote_pos == 0)
		{
			while (vars->cmd[i] == ' ')
			{
				++i;
				++j;
			}
		}
		if (dquote_pos == 0 && quote_pos == 0 && vars->cmd[i] == '"')
			dquote_pos = 1;
		else if (quote_pos == 0 && dquote_pos == 0 && vars->cmd[i] == '\'')
			quote_pos = 1;
		else if (quote_pos == 1 && vars->cmd[i] == '\'')
			quote_pos = 0;
		else if (dquote_pos == 1 && vars->cmd[i] == '"')
			dquote_pos = 0;
	}
	quotes_error(quote_pos, dquote_pos);
	rm_spaces(vars, i - j, quote_pos, dquote_pos);
}

void	del_spaces(t_vars *vars)
{
	vars->cmd = ft_strtrim(vars->cmd, " ");
	vars->cmd_len = ft_strlen(vars->cmd);
	search_quotes(vars, 0, 0, -1);
}
