/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:24:32 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:33:46 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*scpy;

	scpy = (unsigned char *)s;
	while (n > 0)
	{
		if ((unsigned char)*scpy == (unsigned char)c)
			return (scpy);
		scpy++;
		n--;
	}
	return (NULL);
}
