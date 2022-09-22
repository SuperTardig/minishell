/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 08:57:43 by fleduc            #+#    #+#             */
/*   Updated: 2022/08/31 12:28:17 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*buffer;
	int		length;
	int		i;

	length = 0;
	while (s1[length])
		++length;
	buffer = ft_calloc(length + 1, sizeof(char));
	i = -1;
	if (buffer == NULL)
		return (0);
	while (s1[++i])
		buffer[i] = s1[i];
	return (buffer);
}
