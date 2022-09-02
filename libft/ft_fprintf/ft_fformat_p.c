/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fformat_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:40:28 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/02 09:01:15 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static void	ft_fhexa_mem(unsigned long nb, char *base, int *ret, int std)
{
	if (nb >= 16)
		ft_fhexa_mem(nb / 16, base, ret, std);
	ft_fputchar(base[nb % 16], std);
	*ret += 1;
}

int	ft_fformat_p(void *pointer, int std)
{
	int				ret;
	unsigned long	num;

	num = (unsigned long) pointer;
	ret = 0;
	ft_fputstr("0x", std);
	ret += 2;
	ft_fhexa_mem(num, "0123456789abcdef", &ret, std);
	return (ret);
}
