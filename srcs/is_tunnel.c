/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tunnel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:59:34 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/25 19:47:21 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"

int		is_tunnel(char *line, t_room **room_lst)
{
	size_t	i;
	size_t	cmp;
	t_room *cr;

	ft_printf("Testing wether it's a tunnel!\n");
	i = 0;
	cmp = 0;
	cr = *room_lst;
//	ft_printf("this is cr->name %s\n", cr->name);
	while (line[i] != '-' && line[i] != '\0')
		i++;
	if (i == 0)
		return (-1);
	while (cr != NULL)
	{
		if (strncmp(line, cr->name, i) == 0)
		{
			cmp++;
			break;
		}
		cr = cr->next;
	}
	while (*line != '-' && *line)
		line++;
	if (*line == '-')
		line++;
	else
		return (-1);
	cr = *room_lst;
	while (line[i])
		i++;
	while (cr != NULL)
	{
		if (strncmp(line, cr->name, i) == 0)
		{
			cmp++;
			break;
		}
		cr = cr->next;
	}
	if (cmp != 2)
		return (-1);
	return (0);
}
