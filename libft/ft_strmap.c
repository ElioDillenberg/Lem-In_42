/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:12:28 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/11 19:44:15 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*result;
	unsigned int	i;

	i = 0;
	if (s == 0 || !f)
		return (NULL);
	if (!(result = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[i])
	{
		result[i] = f(s[i]);
		i++;
	}
	return (result);
}
