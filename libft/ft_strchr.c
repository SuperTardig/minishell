/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:45:21 by fleduc            #+#    #+#             */
/*   Updated: 2022/08/25 10:53:10 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, char c)
{
	char	*str;

	str = (char *) s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		++str;
	}
	return (str);
}
