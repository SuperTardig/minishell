/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:48:37 by fleduc            #+#    #+#             */
/*   Updated: 2022/10/26 12:38:15 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*buffer;

	buffer = malloc(count * size);
	if (buffer == NULL)
		exit (1);
	ft_bzero(buffer, count * size);
	return (buffer);
}
