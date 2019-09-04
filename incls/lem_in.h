/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:19:27 by edillenb          #+#    #+#             */
/*   Updated: 2019/08/12 17:12:54 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define BUF_SIZE 10000
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
	int				index;
	int				x;
	int				y;
	int				path;
	int				parent;
	struct s_room	*next;
}					t_room;

typedef struct		s_path
{
	int				nb;
	int				len;
	int				index;
	int				ant;
	struct s_path	*next_path;
	struct s_path	*tail_path;
	struct s_path	*next_room;
	struct s_path	*prev_room;
}					t_path;

typedef struct		s_env
{
	t_path			**path_lst;
	t_room			**rm_lst;
	t_room			**rm_lst_path;
	t_room			**rm_tab;
	int				**tu_tab;
	int 			**path_tab;
	char			*to_print;
	char 			*map;
	char			*path;
	char			buffer[BUF_SIZE];
	char			*tmp;
	int       buffer_len;
	int       map_len;
	int				ants_end;
	int				next_ant;
	int				nb_path;
	int				max_path;
	int				nt_rm[2];
	int				rm_len;
	int				ret;
	int				tu_cut;
	int				lf_path;
	int				cr_path;
}					t_env;

/*
******************************** Fonctions *************************************
*/
int					parsing(t_env *env);
/*
******************************** Lem_in.c **************************************
*/
int					set_room_data(char *line, t_room *room, int *command);
int					add_room(char *line, t_room **head, int *command);
/*
*************************** Get_parsing_tool.c *********************************
*/
int					get_command(char *line, int *start_end);
int					get_room(char *line, t_room *room);
int					get_hash(char *name, int len_hash_tab);
int					util_build_room(t_room **rm_lst, t_room *cr, int len);
int					build_room_tab(t_room **rm_lst, t_room ***rm_tab);
/*
*************************** is_parsing_tool.c **********************************
*/
int					is_ant_nb(char *line);
int					is_room(char *line, t_room **room_lst);
/*
******************************** Is_tunnel.c ***********************************
*/
int					is_tunnel(char *line, t_room **room_lst);
void				get_tunnel(t_env *env, char *line);
int					init_tu_tab(int ***tub_tab, int *nt_rm);
/*
******************************** Free.c ****************************************
*/
int					free_all(t_env *env, int opt, int ret);
void				ft_roomdel(t_room **alst);
void				ft_roomdelone(t_room **alst);
void				free_int_tab(t_env *env, int size, int choose);
int					free_room_lst(t_room **head, int opt);
void				ft_pathdel(t_path **path);
void				ft_path_lst_del(t_path **path);
/*
******************************** BFS.c *****************************************
*/
int					add_room_path(t_env *env, t_room *room);
int					delete_room_path(t_env *env);
int 				ft_bfs(t_env *env, int index);
int					add_path_index(t_path **path, int index, t_env *env);
void				add_path_lst(t_env *env, t_path *path);
int					get_path(t_env *env);
int					get_path_2(t_env *env);
void 				reset_path_room(t_env *env);
/*
******************************** util_BFS.c *************************************
*/
void 				set_max_path(t_env *env);
int					check_path(t_env *env);
int					create_path_tab(t_env *env, char *str, int index);
void				free_tab(char **tab);
/*
******************************** Path.c ****************************************
*/
int					find_path(t_env *env, int index, int path_nbr);
int 				get_connection(t_env *env, int i, int index, int path_nbr);
int					get_connection_free(t_env *env, int i, int index, int path_nbr);
int					choose_room(t_env *env, int path_nbr, int index);
/*
******************************** Util_path.c ***********************************
*/
void				make_valid_path(t_env *env);
void				path_finder(t_env *env);
void				delete_path(t_env *env);
void				free_tab(char **tab);
/*
******************************** Util.c ****************************************
*/
void				view_tunnel_by_name(t_env *env);
char				*ft_joinfree(char *s1, char *s2);
char				*ft_strrev(char *str);
char				*ft_strndup(const char *s1, size_t n);
void				print_lst(t_env *env);
int strcat_big(char *src, char **dest, t_env *env);
void reset_buffer(t_env *env);
t_env				*check_buffer(t_env *env, char **dest);
/*
******************************** cut.c ****************************************
*/

void				cut_and_reset(t_env *env, int opt);
int   				get_opti_path(t_env *env);
char				**ft_split(char const *s, char c);

/*
******************************** result.c *************************************
*/

void				result(t_env *env);

#endif
