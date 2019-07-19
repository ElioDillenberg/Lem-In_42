/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:46:22 by abinois           #+#    #+#             */
/*   Updated: 2019/06/20 15:36:21 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

char	*str_times_two(char **str, char ret, int i)
{
	int		x;
	char	*new;

	i = ft_strlen(*str);
	x = (*str)[0] - '0' >= 5 ? i-- + 1 : i--;
	if (!(new = ft_memset(ft_strnew(x), '1', 1)))
		return (ft_free_stropt(str, &new, 1));
	while (i >= 0 && --x >= 0)
	{
		if ((new[x] = ((*str)[i--] - '0') * 2 + ret) > 9)
		{
			ret = 1;
			new[x] -= 10;
		}
		else
			ret = 0;
		new[x] += '0';
	}
	ft_memdel((void**)str);
	return (new);
}

char	*str_by_two(char **str, char ret, int i)
{
	char	*new;
	int		deci;
	char	*final;

	new = "0";
	if (!(new = ft_strjoinfr(str, &new, 1)))
		return (NULL);
	if (!(final = ft_strnew(ft_strlen(new) + 1)))
		return (ft_free_stropt(str, &new, 3));
	while (new[++i])
	{
		deci = (new[i] - '0') / 2 + ret;
		final[i] = deci + '0';
		ret = ((new[i] - '0') * 5) % 10;
	}
	ft_free_stropt(str, &new, 3);
	return (final);
}

char	*get_mantissa(long double dbl, int i, size_t size)
{
	uint8_t	*nb;
	char	*binary;
	uint8_t	mask;

	nb = (uint8_t*)&dbl;
	if (!(binary = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	binary[--size] = '\0';
	while (i < 8)
	{
		mask = 1;
		while (mask)
		{
			binary[--size] = mask & *nb ? 1 + '0' : 0 + '0';
			mask <<= 1;
		}
		i++;
		nb++;
	}
	return (binary);
}

int16_t	get_exponent(long double dbl, t_float **infloat)
{
	int16_t	mask;
	int16_t	*nb;

	mask = 32767;
	nb = (int16_t*)&dbl;
	nb += 4;
	if ((-mask & *nb) == -32768 || dbl < 0)
		(*I)->sign = true;
	*nb &= mask;
	*nb -= 16383;
	return (*nb);
}

int		preci_banks(char **deci, char **fracti, int i)
{
	int		m;

	m = i;
	if ((*fracti)[m++] == '5')
	{
		while ((*fracti)[m] == '0' && (*fracti)[m])
			m++;
		if ((*fracti)[m] != '\0' && (*fracti)[m] != '0')
			return (0);
		if ((*fracti)[m] == '\0')
		{
			if (--i >= 0 && ((*fracti)[i] - '0') % 2 == 1)
				return (0);
			if (i >= 0 && ((*fracti)[i] - '0') % 2 == 0)
				return (1);
			if (i == -1)
			{
				if ((m = ft_strlen(*deci)) && ((*deci)[m - 1] - '0') % 2 == 1)
					return (0);
				if (((*deci)[m - 1] - '0') % 2 == 0)
					return (2);
			}
		}
	}
	return (0);
}
