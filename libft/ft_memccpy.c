/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:14:07 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:33:26 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*cpydst;
	unsigned char	*cpysrc;
	size_t			i;

	cpydst = (unsigned char *)dst;
	cpysrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cpydst[i] = cpysrc[i];
		if (cpydst[i] == (unsigned char)c)
			return (&cpydst[i + 1]);
		i++;
	}
	return (NULL);
}
