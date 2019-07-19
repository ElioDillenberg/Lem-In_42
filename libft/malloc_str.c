/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:06:44 by edillenb          #+#    #+#             */
/*   Updated: 2019/06/20 15:36:46 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char	*malloc_str_d(t_flag flagz, va_list ap)
{
	char	*toa;
	char	*res;
	size_t	lmax;

	F.nb = check_d_i_flagz(flagz, ap);
	if (F.b)
		return (ft_bitoa(&(F.nb), sizeof(F.nb)));
	if (!(toa = ft_lltoa(F.nb)))
		return (NULL);
	lmax = ft_strlen(toa);
	if (F.nb == 0 && F.preci == 0 && F.dot == true)
		lmax = 0;
	if (F.field > lmax)
		lmax = F.field;
	if (F.preci >= F.field && F.preci > lmax)
		lmax = F.nb < 0 ? F.preci + 1 : F.preci;
	if (F.nb > 0 && (F.plus || F.sp) && F.field <= ft_strlen(toa))
		lmax++;
	if (!(res = ft_strnew(lmax)))
		return (ft_free_stropt(&toa, &res, 1));
	return ((res = fill_str_d(F, lmax, &toa, res)));
}

char	*malloc_str_ou(t_flag flagz, va_list ap)
{
	char	*toa;
	char	*res;
	size_t	lmax;

	F.nbou = check_poux_flagz(F, ap);
	if (F.b && F.conv == 'u')
		return (ft_bitoa(&(F.nbou), sizeof(F.nbou)));
	if (!(toa = (F.conv == 'o' ? ft_octatoa(F.nbou) : ft_llutoa(F.nbou))))
		return (NULL);
	lmax = ft_strlen(toa);
	if (F.nbou == 0 && F.preci == 0 && F.dot == true)
		lmax = 0;
	if (F.conv == 'o' && F.hash && F.nbou != 0)
		lmax++;
	if (F.conv == 'o' && F.preci > lmax)
		lmax = F.hash && F.nbou != 0 ? F.preci + 1 : F.preci;
	if (F.conv == 'u' && F.preci > lmax)
		lmax = F.preci;
	if (F.field > lmax)
		lmax = F.field;
	if (!(res = ft_strnew(lmax)))
		return (ft_free_stropt(&toa, &res, 1));
	return ((res = fill_str_ou(F, lmax, &toa, res)));
}

char	*malloc_str_xp(t_flag flagz, va_list ap)
{
	ULL		nb;
	char	*toa;
	char	*res;
	size_t	lmax;

	nb = check_poux_flagz(F, ap);
	if (!(toa = ft_hexatoa(nb)))
		return (NULL);
	lmax = ft_strlen(toa);
	if (nb == 0 && F.conv == 'x')
		F.hash = false;
	if (F.preci > lmax)
		lmax = F.preci;
	if ((F.conv == 'x' && F.hash) || F.conv == 'p')
		lmax += 2;
	if (nb == 0 && F.preci == 0 && F.dot == true && F.conv == 'x')
		lmax = 0;
	if (F.field > lmax)
		lmax = F.field;
	if (!(res = ft_strnew(lmax)))
		return (ft_free_stropt(&toa, &res, 1));
	return ((res = fill_str_xp(F, lmax, &toa, res)));
}

char	*malloc_str_s(t_flag flagz, va_list ap)
{
	char	*toa;
	char	*res;
	size_t	lmax;

	toa = va_arg(ap, char*);
	if (toa == NULL)
		toa = "(null)";
	lmax = ft_strlen(toa);
	if (F.dot)
		lmax = F.preci < lmax ? F.preci : lmax;
	if (F.field > lmax)
		lmax = F.field;
	if (!(res = ft_strnew(lmax)))
		return (NULL);
	return ((res = fill_str_s(F, lmax, toa, res)));
}

char	*malloc_str_c(t_flag flagz, va_list ap, char option, char x)
{
	char	c;
	size_t	lmax;
	char	*res;
	size_t	i;

	c = option == 1 ? x : (char)va_arg(ap, UI);
	i = 0;
	lmax = F.field > 1 ? F.field : 1;
	if (!(res = ft_strnew(lmax)))
		return (NULL);
	if (F.minus)
	{
		res[i++] = (c == 0 ? -1 : c);
		while (i < F.field)
			res[i++] = ' ';
	}
	else
	{
		while (F.field > 1 && i < F.field - 1)
			res[i++] = (F.zer ? '0' : ' ');
		res[i] = (c == 0 ? -1 : c);
	}
	return (res);
}
