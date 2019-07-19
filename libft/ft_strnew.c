/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:10:11 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:49:31 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*new;

	if (!(new = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while ((size + 1) > 0)
		new[size--] = '\0';
	return (new);
}
