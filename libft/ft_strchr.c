/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:45:21 by fleduc            #+#    #+#             */
/*   Updated: 2022/08/31 12:31:26 by fleduc           ###   ########.fr       */
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
