/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:08:23 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/02 09:00:52 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fputchar(unsigned char c, int std)
{
	write(std, &c, 1);
	return (1);
}

int	ft_fputstr(const char *str, int std)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(std, "(null)", 6);
		return (6);
	}
	while (str[i])
		ft_fputchar(str[i++], std);
	return (i);
}

static int	ft_fget_format(const char *format, int index, va_list args, int std)
{
	int	ret;

	ret = 0;
	if (format[index] == 'c')
		ret = ft_fputchar(va_arg(args, int), std);
	else if (format[index] == 's')
		ret = ft_fputstr(va_arg(args, const char *), std);
	else if (format[index] == 'p')
		ret = ft_fformat_p(va_arg(args, void *), std);
	else if (format[index] == 'd' || format[index] == 'i')
		ret = ft_fformat_d_i(va_arg(args, int), std);
	else if (format[index] == 'x' || format[index] == 'X'
		|| format[index] == 'u')
		ret = ft_fformat_x_u(format[index], va_arg(args, unsigned int), std);
	else if (format[index] == '%')
	{
		write(std, "%", 1);
		ret = 1;
	}
	return (ret);
}

int	ft_fprintf(int std, const char *format, ...)
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
			ret += write(std, &format[i], 1);
		else
		{
			ret += ft_fget_format(format, i + 1, args, std);
			++i;
		}
	}
	va_end(args);
	return (ret);
}
