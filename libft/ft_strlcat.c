/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 01:22:10 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:36:25 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t x;
	size_t result;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	x = 0;
	if (size < i)
		result = size + j;
	else
		result = i + j;
	while (src[x] && i + 1 < size)
		dst[i++] = src[x++];
	dst[i] = '\0';
	return (result);
}
