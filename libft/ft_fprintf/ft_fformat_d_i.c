/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fformat_d_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:52:30 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/02 09:01:39 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fformat_d_i(int nb, int std)
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
	ft_putnbr_fd(n, std);
	return (ret);
}
