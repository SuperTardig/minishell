/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:08:23 by fleduc            #+#    #+#             */
/*   Updated: 2022/04/27 14:25:48 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include<stdio.h>

int	ft_putchar(unsigned char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
		ft_putchar(str[i++]);
	return (i);
}

static int	ft_get_format(const char *format, int index, va_list args)
{
	int	ret;

	ret = 0;
	if (format[index] == 'c')
		ret = ft_putchar(va_arg(args, int));
	else if (format[index] == 's')
		ret = ft_putstr(va_arg(args, const char *));
	else if (format[index] == 'p')
		ret = ft_format_p(va_arg(args, void *));
	else if (format[index] == 'd' || format[index] == 'i')
		ret = ft_format_d_i(va_arg(args, int));
	else if (format[index] == 'x' || format[index] == 'X'
		|| format[index] == 'u')
		ret = ft_format_x_u(format[index], va_arg(args, unsigned int));
	else if (format[index] == '%')
	{
		write(1, "%", 1);
		ret = 1;
	}
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		ret;
	va_list	args;

	i = -1;
	ret = 0;
	if (!format)
		return (0);
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] != '%')
			ret += write(1, &format[i], 1);
		else
		{
			ret += ft_get_format(format, i + 1, args);
			++i;
		}
	}
	va_end(args);
	return (ret);
}
