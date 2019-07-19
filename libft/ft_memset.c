/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:27:55 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 17:12:33 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*result;

	result = (unsigned char *)b;
	while (len > 0)
	{
		*result = (unsigned char)c;
		result++;
		len--;
	}
	return (b);
}
