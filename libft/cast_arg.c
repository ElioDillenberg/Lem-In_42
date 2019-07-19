/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:53:38 by edillenb          #+#    #+#             */
/*   Updated: 2019/06/04 14:56:33 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	check_d_i_flagz(t_flag flagz, va_list ap)
{
	long long	number;

	if (F.l)
		return ((number = va_arg(ap, long)));
	if (F.ll)
		return ((number = va_arg(ap, long long)));
	if (F.h)
		return ((number = (short)va_arg(ap, int)));
	if (F.hh)
		return ((number = (char)va_arg(ap, int)));
	return ((number = va_arg(ap, int)));
}

ULL			check_poux_flagz(t_flag flagz, va_list ap)
{
	ULL	number;

	if (F.conv == 'p' || F.conv == 'U')
		return ((number = va_arg(ap, ULL)));
	if (F.l)
		return ((number = va_arg(ap, unsigned long)));
	if (F.ll)
		return ((number = va_arg(ap, ULL)));
	if (F.h)
		return ((number = (unsigned short)va_arg(ap, UI)));
	if (F.hh)
		return ((number = (unsigned char)va_arg(ap, UI)));
	return ((number = va_arg(ap, UI)));
}

long double	check_f_flagz(t_flag flagz, va_list ap)
{
	long double	number;

	if (F.bigl)
		return ((number = va_arg(ap, long double)));
	return ((number = va_arg(ap, double)));
}
