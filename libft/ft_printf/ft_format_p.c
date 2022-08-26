/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:40:28 by fleduc            #+#    #+#             */
/*   Updated: 2022/04/27 14:33:15 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	ft_hexa_mem(unsigned long nb, char *base, int *ret)
{
	if (nb >= 16)
		ft_hexa_mem(nb / 16, base, ret);
	ft_putchar(base[nb % 16]);
	*ret += 1;
}

int	ft_format_p(void *pointer)
{
	int				ret;
	unsigned long	num;

	num = (unsigned long) pointer;
	ret = 0;
	ft_putstr("0x");
	ret += 2;
	ft_hexa_mem(num, "0123456789abcdef", &ret);
	return (ret);
}
