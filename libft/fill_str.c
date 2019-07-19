/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:55:42 by edillenb          #+#    #+#             */
/*   Updated: 2019/06/20 15:37:02 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char	*fill_str_d(t_flag flagz, size_t lmax, char **toa, char *res)
{
	size_t	l_nb;
	size_t	c;

	l_nb = F.nb < 0 ? ft_strlen(*toa) - 1 : ft_strlen(*toa);
	l_nb = F.nb == 0 && F.preci == 0 && F.dot == true ? 0 : l_nb;
	c = 0;
	if (F.minus)
	{
		p_sign(&F, res, &c);
		res = F.preci > l_nb ? p_zer(F.preci, res, &c, l_nb) : res;
		put_sp(F, &c, lmax, p_toa(*toa, res, &c, F));
	}
	else if (F.zer && (!(F.dot) || (F.preci > F.field)))
	{
		p_sign(&F, res, &c);
		p_zer((F.preci > F.field ? F.preci : F.field), res, &c, l_nb);
		p_toa(*toa, res, &c, F);
	}
	else
	{
		put_sp(F, &c, l_nb, res);
		p_toa(*toa, p_zer(F.preci, p_sign(&F, res, &c), &c, l_nb), &c, F);
	}
	ft_memdel((void**)toa);
	return (res);
}

char	*fill_str_ou(t_flag flagz, size_t lmax, char **toa, char *res)
{
	size_t	l_nb;
	size_t	c;

	l_nb = ft_strlen(*toa);
	c = 0;
	if (F.minus)
	{
		p_toa(*toa, put_hash(res, &c, F, l_nb), &c, F);
		put_sp(F, &c, lmax, res);
	}
	else if (F.zer && !F.dot)
	{
		p_zer(F.field, res, &c, l_nb);
		if (F.nbou != 0 || F.preci)
			put_hash(res, &c, F, l_nb);
		p_toa(*toa, res, &c, F);
	}
	else
	{
		put_sp(F, &c, l_nb, res);
		p_toa(*toa, put_hash(res, &c, F, l_nb), &c, F);
	}
	ft_memdel((void**)toa);
	return (res);
}

char	*fill_nomin_xp(t_flag flagz, size_t l_nb, char *res, size_t *c)
{
	if (F.zer && !(F.dot) && F.field > l_nb)
	{
		if (F.hash)
			p_toa("0x", res, c, F);
		while (*c < F.field - l_nb)
			(res)[(*c)++] = '0';
	}
	else
	{
		if (F.field > F.preci && F.field > l_nb)
			while (*c < F.field - (F.preci > l_nb ? F.preci : l_nb))
				(res)[(*c)++] = ' ';
		if (F.hash)
		{
			if (*c >= 2)
				(*c) -= 2;
			else
				(*c) -= *c;
			p_toa("0x", res, c, F);
		}
		p_zer(F.preci, res, c, l_nb);
	}
	return (res);
}

char	*fill_str_xp(t_flag flagz, size_t lmax, char **toa, char *res)
{
	size_t	l_nb;
	size_t	c;

	l_nb = ft_strlen(*toa);
	l_nb = (*toa)[0] == '0' && (*toa)[1] == '\0' && F.preci == 0
		&& F.dot == true && F.conv == 'x' ? 0 : l_nb;
	c = 0;
	res[lmax] = '\0';
	if (F.minus)
	{
		if (F.hash)
			p_toa("0x", res, &c, F);
		p_toa(*toa, p_zer(F.preci, res, &c, l_nb), &c, F);
		put_sp(F, &c, lmax, res);
	}
	else
	{
		fill_nomin_xp(F, l_nb, res, &c);
		if (!(F.dot && F.preci == 0 && (*toa)[0] == '0'))
			p_toa(*toa, res, &c, F);
	}
	ft_memdel((void**)toa);
	return (res);
}

char	*fill_str_s(t_flag flagz, size_t lmax, char *toa, char *res)
{
	size_t	l_toa;
	size_t	c;

	l_toa = ft_strlen(toa);
	if (F.dot)
		l_toa = F.preci < l_toa ? F.preci : l_toa;
	c = 0;
	if (F.minus)
	{
		while (l_toa--)
			res[c++] = *toa++;
		while (c < lmax)
			res[c++] = ' ';
	}
	else
	{
		if (F.field > l_toa)
			while (c < F.field - l_toa)
				res[c++] = F.zer ? '0' : ' ';
		while (l_toa--)
			res[c++] = *toa++;
	}
	return (res);
}
