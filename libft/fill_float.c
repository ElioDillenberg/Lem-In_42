/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:45:46 by abinois           #+#    #+#             */
/*   Updated: 2019/06/20 15:37:24 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char		*get_f_start(t_float **infloat, LD *nb, VL ap, t_flag flagz)
{
	char		*sp;
	int16_t		expo;

	sp = NULL;
	if (!(*I = reset_float(*I)))
		return (NULL);
	*nb = check_f_flagz(F, ap);
	if (F.b)
		return ((*I)->res = ft_bitoa(nb, sizeof(*nb)));
	if (!((*I)->mantissa = get_mantissa(*nb, 0, 65)))
		return (free_float(I));
	expo = get_exponent(*nb, I);
	if (expo == 16384)
		return (inf_or_nan(*I, F, sp, 0));
	(*I)->expo = get_exponent(*nb, I);
	if (!((*I)->deci_str = deci_float(*I, *nb)))
		return (free_float(I));
	if (!((*I)->fracti_str = fracti_float(*I, 0)))
		return (free_float(I));
	if (preci_float(&((*I)->fracti_str), &((*I)->deci_str), F, F.preci) == -1)
		return (free_float(I));
	if (get_zersp(*I, F) == -1)
		return (free_float(I));
	return ("ok!");
}

char		*get_f_min(t_float *infloat, t_flag flagz)
{
	char	*dot;

	dot = ".";
	if (!(I->res = p_sign_float(&(I->deci_str), F, I)))
		return (free_float(&I));
	if (F.hash || F.preci)
		if (!(I->res = ft_strjoinfr(&(I->res), &dot, 1)))
			return (free_float(&I));
	if (F.preci)
		if (!(I->res = ft_strjoinfr(&(I->res), &(I->fracti_str), 3)))
			return (free_float(&I));
	if (I->zersp)
		if (!(I->res = ft_strjoinfr(&(I->res), &(I->zersp), 3)))
			return (free_float(&I));
	return ("ok!");
}

char		*get_f_zer(t_float *infloat, t_flag flagz)
{
	char	*dot;

	dot = ".";
	if (I->zersp)
		if (!(I->deci_str = ft_strjoinfr(&(I->zersp), &(I->deci_str), 3)))
			return (free_float(&I));
	if (!(I->res = p_sign_float(&(I->deci_str), F, I)))
		return (free_float(&I));
	if (F.hash || F.preci)
		if (!(I->res = ft_strjoinfr(&(I->res), &dot, 1)))
			return (free_float(&I));
	if (F.preci)
		if (!(I->res = ft_strjoinfr(&(I->res), &(I->fracti_str), 3)))
			return (free_float(&I));
	return ("ok!");
}

char		*get_f_else(t_float *infloat, t_flag flagz)
{
	char	*dot;

	dot = ".";
	if (!(I->res = p_sign_float(&(I->deci_str), F, I)))
		return (free_float(&I));
	if (I->zersp)
		if (!(I->res = ft_strjoinfr(&(I->zersp), &(I->res), 3)))
			return (free_float(&I));
	if (F.hash || F.preci)
		if (!(I->res = ft_strjoinfr(&(I->res), &dot, 1)))
			return (free_float(&I));
	if (F.preci)
		if (!(I->res = ft_strjoinfr(&(I->res), &(I->fracti_str), 3)))
			return (free_float(&I));
	return ("ok!");
}

char		*get_float(t_flag flagz, va_list ap)
{
	long double	nb;
	t_float		*infloat;
	char		*result;

	I = NULL;
	if (!(result = get_f_start(&I, &nb, ap, F)))
		return (NULL);
	if (ft_strncmp(result, "ok!", 3) == 0 && !F.b)
	{
		if (F.minus)
		{
			if (!(get_f_min(I, F)))
				return (NULL);
		}
		else if (F.zer)
		{
			if (!(get_f_zer(I, F)))
				return (NULL);
		}
		else if (!(get_f_else(I, F)))
			return (NULL);
	}
	result = ft_strdup(I->res);
	free_float(&I);
	return (result);
}
