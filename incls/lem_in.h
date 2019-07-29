/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:19:27 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/29 18:59:20 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdbool.h>

typedef struct		s_room
{
	char			*name;
	bool			start;
	bool			end;
	bool			ant_here;
	size_t			ant;
	int				x;
	int				y;
	struct s_room	*next;
}					t_room;

int		parsing(t_room **rm_lst, int *nt_rm, t_room ***rm_tab, int ***tu_tab);

int		free_room_lst(t_room **head, int opt);
int		set_room_data(char *line, t_room *room, int *command);
int		add_room(char *line, t_room **head, int *command);

void	get_command(char *line, int *command);
int		get_room(char *line, t_room *room);
int		get_hash(char *name, int len_hash_tab);
int		build_room_tab(t_room **rm_lst, t_room ***rm_tab);

int		is_ant_nb(char *line);
int		is_room(char *line, t_room **room_lst);

int		is_tunnel(char *line, t_room **room_lst);
void	get_tunnel(char *line, int *nt_rm, int **tu_tab, t_room **room_tab);
int		init_tu_tab(int ***tub_tab, int *nt_rm);
