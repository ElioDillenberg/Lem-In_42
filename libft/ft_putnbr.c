/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:31:39 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:56:11 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int store;

	if (n < 0)
	{
		ft_putchar('-');
		store = n * -1;
	}
	else
		store = n;
	if (store >= 10)
		ft_putnbr(store / 10);
	ft_putchar(store % 10 + 48);
}
