/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tunnel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:59:34 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/24 12:15:05 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		is_tunnel(char *line, t_room **room_lst)
{
	size_t	i;
	size_t	comp;
	t_room *cr;

	i = 0;
	comp = 0;
	cr = *room_lst;
	while (line[i] != '-' && line[i])
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
