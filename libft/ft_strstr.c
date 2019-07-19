/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 04:25:14 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:37:24 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (haystack[0] == '\0' && needle[0] == '\0')
		return ((char *)&haystack[0]);
	while (haystack[i])
	{
		while (haystack[i + j] == needle[j] && needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		else
		{
			i++;
			j = 0;
		}
	}
	return (NULL);
}
