/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floatools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:48:32 by abinois           #+#    #+#             */
/*   Updated: 2019/06/20 15:36:35 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

char		*p_sign_float(char **str, t_flag flagz, t_float *infloat)
{
	char	*new;
	char	*sign[3];

	sign[0] = "-";
	sign[1] = "+";
	sign[2] = " ";
	new = *str;
	if (I->sign)
	{
		if (!(new = ft_strjoinfr(&(sign[0]), str, 2)))
			return (NULL);
	}
	else if (F.plus)
	{
		if (!(new = ft_strjoinfr(&(sign[1]), str, 2)))
			return (NULL);
	}
	else if (F.sp)
		if (!(new = ft_strjoinfr(&(sign[2]), str, 2)))
			return (NULL);
	*str = NULL;
	return (new);
}

int			get_zersp(t_float *infloat, t_flag flagz)
{
	size_t	z;
	size_t	i;

	z = ft_strlen(I->deci_str) + F.preci;
	z += F.hash || F.preci ? 1 : 0;
	z += I->sign || F.plus || F.sp ? 1 : 0;
	F.field = F.field > z ? F.field - z : 0;
	if (F.field)
	{
		if (!(I->zersp = (char*)malloc(sizeof(char) * (F.field + 1))))
			return (-1);
		i = 0;
		while (F.field--)
			(I->zersp)[i++] = F.zer ? '0' : ' ';
		(I->zersp)[i] = '\0';
		return (0);
	}
	return (0);
}

t_float		*reset_float(t_float *infloat)
{
	if (!(I = (t_float *)malloc(sizeof(t_float))))
		return (NULL);
	I->mantissa = NULL;
	I->sign = false;
	I->expo = 0;
	I->res = NULL;
	I->fracti_str = NULL;
	I->deci_str = NULL;
	I->zersp = NULL;
	return (I);
}

char		*free_float(t_float **infloat)
{
	ft_memdel((void**)&((*I)->mantissa));
	ft_memdel((void**)&((*I)->res));
	ft_memdel((void**)&((*I)->fracti_str));
	ft_memdel((void**)&((*I)->deci_str));
	ft_memdel((void**)&((*I)->zersp));
	ft_memdel((void**)I);
	return (NULL);
}

char		*inf_or_nan(t_float *infloat, t_flag flagz, char *sp, size_t l)
{
	if (I->mantissa[1] == '0' && I->mantissa[2] == '0')
	{
		if (I->sign && !(I->res = ft_strdup("-inf")))
			return (NULL);
		else if (!(I->sign) && F.plus && !(I->res = ft_strdup("+inf")))
			return (NULL);
		else if (!(I->sign) && F.sp && !F.plus && !(I->res = ft_strdup(" inf")))
			return (NULL);
		else if (!(I->sign) && !F.plus && !F.sp && !(I->res = ft_strdup("inf")))
			return (NULL);
	}
	else if (!(I->res = ft_strdup("nan")))
		return (NULL);
	l = ft_strlen(I->res);
	if (F.field > l)
	{
		if (!(sp = ft_memset(ft_strnew(F.field - l), 32, F.field - l)))
			return (NULL);
		if (F.minus && !(I->res = ft_strjoinfr(&(I->res), &sp, 3)))
			return (NULL);
		if (!F.minus && !(I->res = ft_strjoinfr(&sp, &(I->res), 3)))
			return (NULL);
	}
	return ("inf_nan");
}
