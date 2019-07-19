/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:36:22 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:35:14 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;
	size_t s;

	i = 0;
	s = ft_strlen(src);
	while (i < len)
	{
		if (i < s)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i++;
	}
	return (dst);
}
