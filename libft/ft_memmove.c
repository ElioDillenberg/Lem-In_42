/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:28:50 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:33:36 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cpydst;
	unsigned char	*cpysrc;

	cpydst = (unsigned char *)dst;
	cpysrc = (unsigned char *)src;
	if (cpydst <= cpysrc)
		ft_memcpy(cpydst, cpysrc, len);
	else
		while (len-- > 0)
			cpydst[len] = cpysrc[len];
	return (dst);
}
