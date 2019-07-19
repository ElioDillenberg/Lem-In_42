/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:07:45 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/11 14:31:05 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_handle_negative(long *n, long *store, int *len, int *sign)
{
	*store = *n * -1;
	*n *= -1;
	*len += 1;
	*sign = 1;
}

static void		ft_loop(long *store, int *len)
{
	while (*store > 9)
	{
		*store /= 10;
		*len += 1;
	}
}

char			*ft_itoa(int n)
{
	char			*result;
	long			store;
	int				len;
	int				sign;
	long			ncpy;

	ncpy = (long)n;
	store = ncpy;
	len = 1;
	sign = 0;
	if (n < 0)
		ft_handle_negative(&ncpy, &store, &len, &sign);
	ft_loop(&store, &len);
	if (!(result = ft_strnew(len)))
		return (NULL);
	while (len-- > sign)
	{
		result[len] = ncpy % 10 + 48;
		ncpy /= 10;
	}
	if (sign == 1)
		result[0] = '-';
	return (result);
}
