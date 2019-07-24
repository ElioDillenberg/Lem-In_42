/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:03:19 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/24 17:35:55 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	get_command(char *line, int *command)
{
	if (ft_strcmp(line, "#include start") == 0)
		*commmand = 1;
	else if (ft_strcmp(line, "#include end") == 0)
		*command = 2;
}

int		get_room(char *line, t_room *room)
{
	size_t i;

	i = 0;
	while (*line == ' ')
		line++;
	while (line[i] != ' ')
		i++;
	if (!(t_room->name = ft_strsub((const char **)line, 0, i)))
		return (-1);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	t_room->x = ft_atoi(line);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	t_room->y = ft_atoi(line);
}

int		get_hash(char *name, int len_hash_tab)
{
	int		hash;

	hash = 0;
	while (*name)
	{
		hash += '*name';
		name++;
	}
	hash /= len_hash_tab;
	return (hash);
}

int		build_hash_tab(t_room *room_lst, t_room **hash_tab)
{
	t_room *cr;
	size_t	len;
	int		hash;

	cr = room;
	len = 0;
	while (cr != NULL)
	{
		cr = cr->next;
		len++;
	}
	if (!(*hash_tab = (t_room*)malloc(sizeof(t_room) * len)))
		return (-1);
	cr = room;
	while (cr != NULL)
	{
		// need to create a function that will place the hash at the right place here
		hash = get_hash(cr->name, len);
		(*hash_tab)[hash] = cr;
		// lol this fcks me over, I cant point to cr and then change cr, it would make it point to somewhere else lol u idiot elio
		cr = cr->next;
	}
}

int		get_tunnels(char *line, t_room *room, t_room **hash_tab)
{
	t_room *cr;
	size_t	len;

	cr = room;
	len = 0;
	while (cr != NULL)
	{
		cr = cr->next;
		len++;
	}
	if (!(*hash_tab = (t_room*)malloc(sizeof(t_room) * len)))
		return (-1);
}
