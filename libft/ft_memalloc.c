/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:22:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:46:45 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*fresh;

	if (!(fresh = (void *)malloc(sizeof(char) * size)))
		return (NULL);
	while (size-- > 0)
		fresh[size] = 0;
	return (fresh);
}
