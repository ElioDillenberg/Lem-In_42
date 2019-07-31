/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:19:27 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/30 16:55:30 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <string.h>
# include <stdbool.h>

/*
******************************** Structures ************************************
*/

typedef struct		s_room
{
	char			*name;
	bool			start;
	bool			end;
	bool			ant_here;
	size_t			ant;
	int       index;
	int				x;
	int				y;
	int       path;
	struct s_room	*next;
}					t_room;

typedef struct		s_env
{
	t_room			**rm_lst;
	t_room			**rm_tab;
	int				**tu_tab;
	char			*to_print;
	char      *path;
	int       no_path;
	int       nb_path;
	int				nt_rm[2];
	int				rm_len;
	int				ret;
}					t_env;

/*
******************************** Fonctions *************************************
*/
int					parsing(t_env *env);

int					set_room_data(char *line, t_room *room, int *command);
int					add_room(char *line, t_room **head, int *command);

void				get_command(char *line, int *command);
int					get_room(char *line, t_room *room);
int					get_hash(char *name, int len_hash_tab);
int					util_build_room(t_room **rm_lst, t_room *cr, int len);
int					build_room_tab(t_room **rm_lst, t_room ***rm_tab);

int					is_ant_nb(char *line);
int					is_room(char *line, t_room **room_lst);

int					is_tunnel(char *line, t_room **room_lst);
void				get_tunnel(t_env *env, char *line);
int					init_tu_tab(int ***tub_tab, int *nt_rm);

int					free_all(t_env *env, int opt);
void				ft_roomdel(t_room **alst);
void				ft_roomdelone(t_room **alst);
void				free_int_tab(t_env *env, int size);
int					free_room_lst(t_room **head, int opt);

int find_path(t_env *env, int index, int path_nbr);
int  get_connection(t_env *env, int i, int index, int path_nbr);
void make_valid_path(t_env *env);

void view_tunnel_by_name(t_env *env);
char *ft_joinfree(char *s1, char *s2);
char *ft_strrev(char *str);
char	*ft_strndup(const char *s1, size_t n);
#endif
