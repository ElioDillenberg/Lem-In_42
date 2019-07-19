/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:28:27 by abinois           #+#    #+#             */
/*   Updated: 2019/06/20 15:37:12 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char		*p_toa(char *toa, char *res, size_t *c, t_flag flagz)
{
	size_t	i;

	i = *toa == '-' ? 1 : 0;
	if (toa[0] == '0' && toa[1] == 0 && F.dot && F.preci == 0
			&& F.conv != 'p' && !F.hash)
	{
		if ((F.conv == 'o' || F.conv == 'u') && F.field)
			res[(*c)] = ' ';
		return (res);
	}
	while (toa[i])
		res[(*c)++] = toa[i++];
	return (res);
}

char		*p_sign(t_flag *flagz, char *res, size_t *c)
{
	if (!(F->minus) && (!(F->zer) || F->dot) && ((F->nb < 0 || F->plus || F->sp)
				&& *c != 0))
		(*c)--;
	if (F->nb < 0)
		res[(*c)++] = '-';
	else if (F->plus && F->nb >= 0)
		res[(*c)++] = '+';
	else if (F->sp && F->nb >= 0)
		res[(*c)++] = ' ';
	if (!(F->minus) && F->zer && !(F->dot) && *c == 1 && F->field > 0)
		F->field--;
	return (res);
}

char		*p_zer(size_t flag, char *res, size_t *c, size_t l_nb)
{
	if (flag > l_nb)
	{
		while (l_nb++ < flag)
			res[(*c)++] = '0';
	}
	return (res);
}

char		*put_hash(char *res, size_t *c, t_flag flagz, size_t l_nb)
{
	p_zer(F.preci, res, c, l_nb);
	if (F.conv == 'o' && F.hash)
	{
		if (F.preci > l_nb)
			return (res);
		if (*c == 0 && F.nbou != 0)
			res[(*c)++] = '0';
		else if (F.field > l_nb && !(F.dot && !F.preci && F.nbou == 0))
			res[(*c) - 1] = '0';
	}
	return (res);
}

char		*put_sp(t_flag flagz, size_t *c, size_t lmax, char *res)
{
	if (F.minus)
	{
		if (F.field > F.preci)
			while (*c < lmax)
				res[(*c)++] = ' ';
	}
	else if (F.field > lmax && F.field > F.preci)
		while (*c < F.field - (F.preci > lmax ? F.preci : lmax))
			res[(*c)++] = ' ';
	return (res);
}
