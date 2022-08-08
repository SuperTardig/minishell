/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:04:55 by fleduc            #+#    #+#             */
/*   Updated: 2022/04/04 13:08:30 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = ft_strlen(s);
	str = (char *) s + i;
	if (c == '\0')
		return (str);
	while (i-- >= 0)
	{
		if (*str == (char) c)
			return (str);
		--str;
	}
	return (0);
}
