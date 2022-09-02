/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fformat_x_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:09:30 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/02 09:01:06 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_fhexa_convert(unsigned int nb, char *base, int *ret, int std)
{
	if (nb >= 16)
		ft_fhexa_convert(nb / 16, base, ret, std);
	ft_fputchar(base[nb % 16], std);
	*ret += 1;
}

void	ft_fputnbr(unsigned int nb, int *ret, int std)
{
	if (nb >= 10)
		ft_fputnbr(nb / 10, ret, std);
	ft_fputchar((nb % 10) + '0', std);
	*ret += 1;
}

int	ft_fformat_x_u(char c, unsigned int nb, int std)
{
	int	ret;

	ret = 0;
	if (c == 'X')
		ft_fhexa_convert(nb, "0123456789ABCDEF", &ret, std);
	else if (c == 'x')
		ft_fhexa_convert(nb, "0123456789abcdef", &ret, std);
	else if (c == 'u')
		ft_fputnbr(nb, &ret, std);
	return (ret);
}
