/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:49:30 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:57:30 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int store;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		store = n * -1;
	}
	else
		store = n;
	if (store >= 10)
		ft_putnbr_fd(store / 10, fd);
	ft_putchar_fd(store % 10 + 48, fd);
}
