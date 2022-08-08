/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:20:04 by fleduc            #+#    #+#             */
/*   Updated: 2022/05/05 12:56:03 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	nb_size(int n)
{
	int	size;

	size = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		++size;
	}
	if (n < 0)
		++size;
	return (size);
}

char	*ft_itoa(int n)
{
	char		*str_nb;
	int			size;
	long int	nb;

	nb = n;
	size = nb_size(nb);
	str_nb = ft_calloc(size + 1, sizeof(char));
	if (str_nb == NULL)
		return (0);
	if (nb < 0)
	{
		str_nb[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str_nb[0] = '0';
	while (nb > 0)
	{
		str_nb[size - 1] = (nb % 10) + '0';
		nb /= 10;
		--size;
	}	
	return (str_nb);
}
