/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 11:38:10 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/29 18:39:46 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>

/*
** Here under the function that will handle the entire parsing of input
** it checks input thanks to GNL and stores the entire input into a string
** which will be used in the end to display the ant farm
** lot can be optmizied here I believe, it's easier to have a clear view at
** start tho
*/

static int	exit_parsing(char **line, int ret)
{
	ft_memdel((void**)line);
	get_next_line(0, line, 0);
	return (ret);
}

/*
** 
**
*/

int			parsing(t_room **rm_lst, int *nt_rm, t_room ***rm_tab, int ***tu_tab)
{
	char	*to_print = NULL;
	char	*line;
	int		index;
	int		command;
	int		ret;

	command = 0;
	index = 0;
	while ((ret = get_next_line(0, &line, 1)) && ret != -1 && ret != 0)
	{
		if (line[0] == '#' && line[1] != '#')
		{
			if (!(to_print = ft_strjoinlemin(&to_print, &line, 1)))
				return (exit_parsing(&line, -1));
		}
		else if (line[0] == '#' && line[1] == '#')
		{
			get_command(line, &command);
			if (!(to_print = ft_strjoinlemin(&to_print, &line, 1)))
				return (exit_parsing(&line, -1));
		}
		else if (index == 0 && is_ant_nb(line) != -1)
		{
			nt_rm[0] = ft_atoui(line);
			if (!(to_print = ft_strjoinlemin(&to_print, &line, 1)))
				return (exit_parsing(&line, -1));
			index++;
		}
		else if (index == 1)
		{
			if (is_room(line, rm_lst) != -1)
			{
				if (add_room(line, rm_lst, &command) == -1)
					return (exit_parsing(&line, -1));
				if (!(to_print = ft_strjoinlemin(&to_print, &line, 1)))
					return (exit_parsing(&line, -1));
			}
			else if (is_tunnel(line, rm_lst) != -1)
			{
				if (!(nt_rm[1] = build_room_tab(rm_lst, rm_tab)))
					return (exit_parsing(&line, -1));
				if (init_tu_tab(tu_tab, nt_rm) == -1)
					return (exit_parsing(&line, -1));
				get_tunnel(line, nt_rm, *tu_tab, *rm_tab);
				index++;
				if (!(to_print = ft_strjoinlemin(&to_print, &line, 1)))
					return (exit_parsing(&line, -1));
			}
			else
				return (exit_parsing(&line, 0));
		}
		else if (index == 2 && is_tunnel(line, rm_lst) != -1)
		{
			get_tunnel(line, nt_rm, *tu_tab, *rm_tab);
			if (!(to_print = ft_strjoinlemin(&to_print, &line, 1)))
				return (exit_parsing(&line, -1));
		}
		else
			return (exit_parsing(&line, 0));
		ft_memdel((void**)&line);
	}
	ft_putstr(to_print);
	ft_memdel((void**)&to_print);
	return (exit_parsing(&line, 0));
}
