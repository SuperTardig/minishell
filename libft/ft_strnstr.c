/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:56:10 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/07 13:22:02 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
		return ((char *) haystack);
	while (haystack[i] && len > i)
	{
		j = 0;
		while ((i + j) < len && needle[j] == haystack[i + j])
		{
			++j;
			if (needle[j] == '\0')
				return ((char *) &haystack[i]);
		}
		++i;
	}
	return (0);
}
