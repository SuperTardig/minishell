/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:52:30 by fleduc            #+#    #+#             */
/*   Updated: 2022/04/08 11:56:21 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_format_d_i(int nb)
{
	int		n;
	int		ret;

	ret = 0;
	n = nb;
	if (nb < 0)
		ret++;
	else if (nb == 0)
		ret++;
	while (nb > 0 || nb < 0)
	{
		++ret;
		nb /= 10;
	}
	ft_putnbr_fd(n, 1);
	return (ret);
}
