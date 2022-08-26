/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:10:47 by fleduc            #+#    #+#             */
/*   Updated: 2022/04/29 16:21:18 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<stdarg.h>
# include<unistd.h>
# include<stdlib.h>
# include "../libft.h"

int		ft_printf(const char *str, ...);
int		ft_putchar(unsigned char c);
int		ft_putstr(const char *str);
int		ft_format_p(void *pointer);
int		ft_format_d_i(int nb);
int		ft_format_x_u(char c, unsigned int nb);

void	ft_hexa_convert(unsigned int nb, char *base, int *ret);
void	ft_putnbr(unsigned int nb, int *ret);

#endif
