/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:18:17 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:49:49 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void	ft_strdel(char **as)
{
	if (as == 0)
		return ;
	free(*as);
	*as = NULL;
}
