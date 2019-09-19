/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tunnel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:59:34 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/17 18:28:48 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>

int			init_tu_tab(t_tunnel ***tu_tab, int *nt_rm)
{
	int	i;
	int nb;

	ft_printf("nt_rm[1] = %d\n", nt_rm[1]);
	nb = nt_rm[1];
	i = 0;
	if (!(*tu_tab = (t_tunnel **)ft_memalloc(sizeof(t_tunnel*) * nb)))
		return (-1);
	while (i < nt_rm[1])
		if (!((*tu_tab)[i++] = (t_tunnel*)ft_memalloc(sizeof(t_tunnel) * nb)))
			return (-1);
	return (0);
}

static int	check_tunnel(char *line, int opt, int i)
{
	if (line[i] == '\0' && opt == 1)
		return (-2);
	if (line[i] == '-')
		line[i] = '\0';
	else
		return (-1);
	return (1);
}

static int	check_tunnel_name(char *line, t_room *cr, size_t *cmp, int step)
{
	if (step == 1)
	{
		while (cr != NULL)
		{
			if (ft_strcmp(line, cr->name) == 0)
			{
				*cmp = (*cmp) + 1;
				break ;
			}
			cr = cr->next;
		}
		return (1);
	}
	while (cr != NULL)
	{
		if (ft_strcmp(line, cr->name) == 0)
		{
			*cmp = (*cmp) + 1;
			break ;
		}
		cr = cr->next;
	}
	return (*cmp != 2 ? -2 : 1);
}

int			is_tunnel(char *line, t_room **room_lst, int opt)
{
	size_t	i;
	t_room	*cr;
	size_t	cmp;

	i = 0;
	cmp = 0;
	cr = *room_lst;
	while (line[i] != '-' && line[i] != '\0')
		i++;
	if (check_tunnel(line, opt, i) != 1)
		return (check_tunnel(line, opt, i));
	check_tunnel_name(line, cr, &cmp, 1);
	line[i] = '-';
	while (*line != '-' && *line != '\0')
		line++;
	if (*line == '-')
		line++;
	else
		return (-1);
	if (check_tunnel_name(line, cr, &cmp, 2) == -2)
		return (-2);
	return (0);
}
