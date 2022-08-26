/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:56:40 by fleduc            #+#    #+#             */
/*   Updated: 2022/04/04 11:23:25 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check_char(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*buffer;

	j = 0;
	k = 0;
	if (s1 == NULL || set == NULL)
		return (0);
	i = ft_strlen(s1);
	while (s1[j] && check_char(set, s1[j]))
		++j;
	while (i > j && check_char(set, s1[i - 1]))
		--i;
	buffer = ft_calloc(i - j + 1, sizeof(char));
	if (buffer == NULL)
		return (0);
	while (j < i)
		buffer[k++] = s1[j++];
	return (buffer);
}
