/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:10:47 by fleduc            #+#    #+#             */
/*   Updated: 2022/09/02 09:00:36 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include<stdarg.h>
# include<unistd.h>
# include<stdlib.h>
# include "../libft.h"

int		ft_fprintf(int std, const char *str, ...);
int		ft_fputchar(unsigned char c, int std);
int		ft_fputstr(const char *str, int std);
int		ft_fformat_p(void *pointer, int std);
int		ft_fformat_d_i(int nb, int std);
int		ft_fformat_x_u(char c, unsigned int nb, int std);

void	ft_fhexa_convert(unsigned int nb, char *base, int *ret, int std);
void	ft_fputnbr(unsigned int nb, int *ret, int std);

#endif
