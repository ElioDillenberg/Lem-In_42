/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:02:46 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:51:45 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strnequ(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	if (n == 0)
		return (1);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < (n - 1))
		i++;
	if (!(s1[i] == s2[i]))
		return (0);
	return (1);
}
