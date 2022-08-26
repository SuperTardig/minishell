/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:09:30 by fleduc            #+#    #+#             */
/*   Updated: 2022/04/11 09:45:04 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_hexa_convert(unsigned int nb, char *base, int *ret)
{
	if (nb >= 16)
		ft_hexa_convert(nb / 16, base, ret);
	ft_putchar(base[nb % 16]);
	*ret += 1;
}

void	ft_putnbr(unsigned int nb, int *ret)
{
	if (nb >= 10)
		ft_putnbr(nb / 10, ret);
	ft_putchar((nb % 10) + '0');
	*ret += 1;
}

int	ft_format_x_u(char c, unsigned int nb)
{
	int	ret;

	ret = 0;
	if (c == 'X')
		ft_hexa_convert(nb, "0123456789ABCDEF", &ret);
	else if (c == 'x')
		ft_hexa_convert(nb, "0123456789abcdef", &ret);
	else if (c == 'u')
		ft_putnbr(nb, &ret);
	return (ret);
}
