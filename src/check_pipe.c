/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:29:09 by bperron           #+#    #+#             */
/*   Updated: 2022/10/06 10:35:34 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_pipe(t_vars *vars)
{
	int	i;
	int	nb_pipe;

	i = -1;
	vars->nb_pipe = 0;
	while (vars->cmd[++i])
		if (vars->cmd[i] == '|')
			vars->nb_pipe++;
	vars->piped = ft_calloc(sizeof(char *), vars->nb_pipe + 2);
	i = 0;
	nb_pipe = vars->nb_pipe;
	while (nb_pipe-- >= 0)
	{
		vars->piped[i++] = ft_substr(vars->cmd, 0,
				ft_strlen_until(vars->cmd, '|'));
		while (*vars->cmd != '|' && *vars->cmd)
			vars->cmd++;
		vars->cmd++;
		while (*vars->cmd == ' ' && *vars->cmd)
			vars->cmd++;
	}
	vars->piped[i] = NULL;
}

int	count_args(t_vars *vars)
{
	int	i;
	int	j;
	int	nb;
	
	i = -1;
	nb = 1;
	while (vars->piped[++i])
	{
		j = -1;
		while (vars->piped[i][++j])
		{
			if (vars->piped[i][j] == '"')
			{
				while (vars->piped[i][++j] != '"')
					(void) j;
			}
			else if (vars->piped[i][j] == '\'')
			{
				while (vars->piped[i][++j] != '\'')
					(void) j;
			}
			else if (vars->piped[i][j] == ' ')
				nb++;
		}
	}
	return (nb);
}

int	find_size(t_vars *vars, int row)
{
	int	i;

	i = -1;
	while (vars->piped[row][++i])
	{
		if (vars->piped[row][i] == '"' || vars->piped[row][i] == '\'')
			i--;
		if (vars->piped[row][i] == ' ')
			return (i);
	}
	return (i);
}



//faut trouver la taille de la string a mettre dedans
//pas sur pour les quotes si jen creer ne autre si yas pas despaces je lai fait qui en creer pas
//les guillemets marche pas
void	split_args(t_vars *vars)
{
	char	**new_piped;
	int		i;
	int		j;
	int		k;
	int		l;
	int		quotes;
	
	new_piped = ft_calloc(count_args(vars) + 2, sizeof(char *));
	i = 0;
	k = 0;
	j = 0;
	l = 0;
	quotes = 0;
	while (vars->piped[i][j] == ' ')
		j++;
	while (vars->piped[i])
	{
		if (vars->piped[i][j] == ' ' && (quotes % 2) != 1)
		{
			l = 0;
			k++;
			while (vars->piped[i][j] == ' ')
				j++;
		}
		if (vars->piped[i][j] == '"' || vars->piped[i][j] == '\'')
			quotes++;
		if (!(new_piped[k]))
			new_piped[k] = ft_calloc(find_size(vars, i) + 1, sizeof(char));
		new_piped[k][l++] = vars->piped[i][j++];
		if (!(vars->piped[i][j]))
		{
			i++;
			j = 0;
			l = 0;
		}
	}
	for (int a = 0; new_piped[a]; a++)
		printf("%s\n", new_piped[a]); 
}