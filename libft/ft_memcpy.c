/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:24:59 by fleduc            #+#    #+#             */
/*   Updated: 2022/03/31 13:25:25 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*dest;
	const char		*source;

	dest = dst;
	source = src;
	if (src == NULL && dst == NULL)
		return (0);
	while (n-- > 0)
		*dest++ = *source++;
	return (dst);
}
