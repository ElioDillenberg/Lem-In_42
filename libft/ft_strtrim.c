/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:26:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/06/20 15:59:14 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*result;
	size_t			len;
	unsigned int	i;

	i = 0;
	if (s == 0)
		return (NULL);
	len = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (i != len)
		while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
			len--;
	if (!(result = ft_strsub((const char**)&s, i, (len - i), 0)))
		return (NULL);
	return (result);
}
