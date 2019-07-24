/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 11:38:10 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/24 17:35:57 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*to_print;
	char	*line;
	int		index;
	int		command;

	command = 0;
	index = 0;
	while ((ret = get_next_line(0, &line, 1)) && ret != -1 && ret != 0)
	{
		if (line[0] == '#' && line[1] != '#')
		{
			if (!(to_print = ft_strjoinfr(to_print, line, 1)))
				return (exit_parsing(&line, -1));
		}
		else if (line[0] == '#' && line[1] == '#')
		{
			get_command(line, &command);
			if (!(to_print = ft_strjoinfr(to_print, line, 1)))
				return (exit_parsing(&line, -1));
		}
		else if (index == 0 && is_ant_nb(line))
		{
			*nb_ants = ft_atoui(line);
			if (!(to_print = ft_strjoinfr(to_print, line, 1)))
				return (exit_parsing(&line, -1));
			index++;
		}
		else if (index == 1)
		{
			if (is_room(line) != -1)
			{
				if (!(add_room(line, room_lst, &command)))
					return (exit_parsing(&line, -1));
				if (!(to_print = ft_strjoinfr(to_print, line, 1)))
					return (exit_parsing(&line, -1));
			}
			else if (is_tunnel(line) != -1)
			{
				build_hash_tab(t_room *room_lst, t_room **hash_tab);
				get_tunnel(line, room_lst, &index);
				if (!(to_print = ft_strjoinfr(to_print, line, 1)))
					return (exit_parsing(&line, -1));
			}
			else
				return (exit_parsing(&line, 0));
		}
		else if (index == 2 && is_tunnel(line))
			get_tunnel(line, room_lst, &index);
		else
			return (exit_parsing(&line, 0));
		}
		ft_memdel((void**)&line);
	}
	return (exit_parsing(&line, 0));
}
