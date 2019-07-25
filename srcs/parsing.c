/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 11:38:10 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/25 19:47:18 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"

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

int			parsing(t_room **room_lst, size_t *nb_ants)
{
//	char	*to_print;
	char	*line;
	int		index;
	int		command;
	int		ret;

	command = 0;
	index = 0;
	ft_printf("Start of parsing\n");
	while ((ret = get_next_line(0, &line, 1)) && ret != -1 && ret != 0)
	{
		ft_printf("While parsing loop\n");
		if (line[0] == '#' && line[1] != '#')
		{
			ft_printf("This is a comment!\n");
	//		if (!(to_print = ft_strjoinfr(&to_print, &line, 1)))
		//		return (exit_parsing(&line, -1));
		}
		else if (line[0] == '#' && line[1] == '#')
		{
			ft_printf("This is a command!\n");
			get_command(line, &command);
			ft_printf("Just found this command: %s\n", line);
	//		if (!(to_print = ft_strjoinfr(&to_print, &line, 1)))
		//		return (exit_parsing(&line, -1));
		}
		else if (index == 0 && is_ant_nb(line) != -1)
		{
			ft_printf("This is the number of ants!\n");
			*nb_ants = ft_atoui(line);
			ft_printf("nb of ants = %u\n", *nb_ants);
	//		if (!(to_print = ft_strjoinfr(&to_print, &line, 1)))
		//		return (exit_parsing(&line, -1));
			index++;
			ft_printf("end of nb of ants!\n");
		}
		else if (index == 1)
		{
			ft_printf("Is it a room or a tunnel?\n");
			if (is_room(line, room_lst) != -1)
			{
				ft_printf("This is a valid room!\n");
				if (add_room(line, room_lst, &command) == -1)
					return (exit_parsing(&line, -1));
		//		if (!(to_print = ft_strjoinfr(&to_print, &line, 1)))
			//		return (exit_parsing(&line, -1));
			}
			else if (is_tunnel(line, room_lst) != -1)
			{
		//		build_hash_tab(t_room *room_lst, t_room **hash_tab);
		//		get_tunnel(line, room_lst, &index)
				ft_printf("this is the first valid tunnel %s\n", line);
				index++;
		//		if (!(to_print = ft_strjoinfr(&to_print, &line, 1)))
			//		return (exit_parsing(&line, -1));
			}
			else
				return (exit_parsing(&line, 0));
		}
		else if (index == 2 && is_tunnel(line, room_lst) != -1)
		{
			ft_printf("found a valid tunnel : %s\n", line);
	//		if (!(to_print = ft_strjoinfr(&to_print, &line, 1)))
		//		return (exit_parsing(&line, -1));
			//get_tunnel(line, room_lst, &index);
		}
		else
			return (exit_parsing(&line, 0));
		ft_memdel((void**)&line);
		ft_printf("Bottom of parsing while loop\n\n");
	}
	return (exit_parsing(&line, 0));
}
