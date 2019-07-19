/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:34:07 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:26:30 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*cpydst;
	const unsigned char	*cpysrc;

	cpydst = (unsigned char *)dst;
	cpysrc = (const unsigned char *)src;
	while (n > 0)
	{
		*cpydst++ = *cpysrc++;
		n--;
	}
	return (dst);
}
