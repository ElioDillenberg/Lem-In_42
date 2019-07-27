/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfrendl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 16:58:48 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/27 17:42:55 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	handle_first(char **new, char **s2)
{
	size_t	len;
	int		i;

	i = -1;
	len = ft_strlen(*s2);
	if (!(*new = (char*)malloc(sizeof(char) * len + 2)))
		return (-1);
	while ((*s2)[++i])
		(*new)[i] = (*s2)[i];
	(*new)[i++] = '\n';
	(*new)[i] = '\0';
	ft_memdel((void**)s2);
	return (0);
}

char		*ft_strjoinfrendl(char **s1, char **s2, char option)
{
	char	*new;
	size_t	len;
	int		i;

	new = NULL;
	if (*s1 == NULL && *s2)
	{
		if (handle_first(&new, s2) == -1)
			return ((char*)ft_free_stropt(s1, s2, option));
	}
	else if (*s1 && *s2)
	{
		len = ft_strlen(*s1) + ft_strlen(*s2);
		if (!(new = (char*)malloc(sizeof(*new) * len + 2)))
			return ((char*)ft_free_stropt(s1, s2, option));
		i = -1;
		while ((*s1)[++i])
			new[i] = (*s1)[i];
		len = 0;
		while ((*s2)[len])
			new[i++] = (*s2)[len++];
		new[i++] = '\n';
		new[i] = '\0';
	}
	ft_free_stropt(s1, s2, option);
	return (new);
}
