/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:43:22 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/22 16:43:44 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_atoui(const char *str)
{
	size_t	i;
	size_t	atoui;

	atoui = 0;
	i = 0;
	while ((str[i] == 32 || (9 <= str[i] && str[i] <= 13)) && str[i])
		i++;
	while (ft_isdigit(str[i]) && str[i])
	{
		atoui = atoui * 10 + (str[i] - 48);
		i++;
	}
	return (atoui);
}
