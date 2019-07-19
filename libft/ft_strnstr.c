/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 04:54:06 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:38:53 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*ft_strnstr(const char *hstck, const char *ndl, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (hstck[0] == '\0' && ndl[0] == '\0')
		return ((char *)&hstck[0]);
	while (hstck[i] && i <= len)
	{
		while (hstck[i + j] == ndl[j] && ndl[j] && (i + j) < len)
			j++;
		if (ndl[j] == '\0')
			return ((char *)&hstck[i]);
		else
		{
			i++;
			j = 0;
		}
	}
	return (NULL);
}
