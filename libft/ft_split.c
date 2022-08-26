/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:16:01 by fleduc            #+#    #+#             */
/*   Updated: 2022/04/08 16:12:28 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_seps(char const *s, char c)
{
	int	i;
	int	sep;

	i = 0;
	sep = 0;
	if (!s[0])
		return (0);
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c)
			|| (s[i] != c && s[i + 1] == '\0'))
			++sep;
		++i;
	}
	return (sep);
}

static int	len_of_str(char const *s, char c, int index)
{
	int	i;

	i = 0;
	while (index >= 0 && s[index] != c)
	{
		++i;
		--index;
	}
	return (i);
}

static char	*new_str(char const *s, char c, int index)
{
	int		start;
	int		str_len;
	int		i;
	char	*buffer;

	i = 0;
	str_len = len_of_str(s, c, index);
	start = index - str_len + 1;
	buffer = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (i < str_len)
		buffer[i++] = s[start++];
	return (buffer);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		nb_sep;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	nb_sep = count_seps(s, c);
	split = (char **)ft_calloc(nb_sep + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			split[j++] = new_str(s, c, i);
		++i;
	}
	return (split);
}
