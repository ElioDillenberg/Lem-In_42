/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 03:23:53 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/08 20:03:20 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	cc;

	cc = c;
	len = ft_strlen(s);
	while (s[len] != cc)
		if (len-- == 0)
			return (NULL);
	return ((char *)&s[len]);
}
