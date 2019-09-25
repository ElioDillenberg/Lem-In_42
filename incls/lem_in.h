/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:19:27 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/25 14:53:43 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define BUF_SIZE 4096
# include <string.h>
# include <stdbool.h>

/*
******************************** Structures ************************************
*/

typedef struct		s_tunnel
{
	int		index;
	int		status;
	bool	exist;
}					t_tunnel;

typedef struct		s_parse
{
	int		start_end[2];
	int		index;
	int		start;
	int		end;
	int		command;
	int		ret;
	int		fd;
	char	*line;
}					t_parse;

typedef struct		s_room
{
	char			*name;
	bool			start;
	bool			end;
	bool			visited;
	size_t			ant;
	int				index;
	int				x;
	int				y;
	int				path;
	int				*dad;
	int				nb_dad;
	int				path_tt;
	int				parent_tt;
	int				parent;
	int				dfs;
	int				dfs_tt;
	struct s_room	*next;
}					t_room;

typedef struct		s_path
{
	int				nb;
	int				len;
	int				index;
	int				ant;
	int				strt_ants;
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
	t_room			**rm_lst_path_tt;
	t_room			**rm_tab;
	t_parse			*parse;
	t_tunnel		**tu_tab;
	int				**path_tab;
	char			*to_print;
	char			*map;
	char			*path;
	char			buffer[BUF_SIZE];
	char			*tmp;
	int				buffer_len;
	int				map_len;
	int				ants_end;
	int				next_ant;
	int				nb_path;
	int				max_path;
	int				nt_rm[2];
	int				rm_len;
	int				ret;
	int				tu_cut;
	int				did_cut;
	int				lf_path;
	int				cr_path;
	int				round;
	int				mod_ants;
	int				total_rounds;
	int				opt_rounds;
	char			*opt_file_path;
	int				opt_paths;
	int				opt_double;
	int				finish;
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
int					get_room_tab(t_env *env, int len);
int					get_tunnel(t_env *env, char *line);
/*
******************************* Build.c ****************************************
*/
int					build_room_tab(t_env *env);
/*
*************************** is_parsing_tool.c **********************************
*/
int					is_ant_nb(char *line);
int					is_room(char *line, t_room **room_lst, t_env *env);
int					is_coordinate(char *line);
/*
***************************** Check_parsing.c **********************************
*/
int					check_coordinates_lst(int x, int y, t_room **room_lst);
int					check_coordinates(char *line, t_room **room_lst);
int					check_name(t_room *cr, char *test);
int					check_room(char *line);
/*
******************************** Is_tunnel.c ***********************************
*/
int					is_tunnel(char *line, t_room **room_lst, int opt, size_t i);
int					init_tu_tab(t_tunnel ***tub_tab, int *nt_rm);
/*
******************************** Free.c ****************************************
*/
int					free_all(t_env *env, int ret);
int					free_room_lst(t_room **head);
void				ft_pathdel(t_path **path);
void				ft_path_lst_del(t_path **path);
/*
******************************** BFS.c *****************************************
*/
int					add_room_path(t_env *env, t_room *room);
void				delete_room_path(t_env *env);
int					ft_bfs(t_env *env, int index);
int					ft_better_way(t_env *env, int index);
/*
******************************** Room.c ****************************************
*/
int					set_room_data(char *line, t_room *room, int *start_end);
int					add_room(char *line, t_room **head, int *command);
int					ft_roomdel(t_room **room, int ret);
void				ft_roomdelone(t_room **room);
/*
******************************** Cut.c ****************************************
*/

void				cut_and_reset(t_env *env, int opt, int visited);
char				**ft_split(char const *s, char c);
void				reset_path_room(t_env *env, int opt);
/*
******************************** Result.c *************************************
*/
int					get_strt_ants(t_env *env, int rounds, int mod);
int					result(t_env *env);
int					set_ant_start(t_path *cr, int *rounds_cr,
					int *mod_cr, t_env *env);
/*
******************************** Option.c *************************************
*/
int					usage();
int					print_path(t_env *env);
int					get_option(t_env *env, char **argv, int argc);
/*
********************************** buffer.c ************************************
*/
int					strcat_big(char *src, char **dest, t_env *env);
void				reset_buffer(t_env *env);
t_env				*check_buffer(t_env *env, char **dest);
/*
********************************** Path.c **************************************
*/
void				set_max_path(t_env *env);
int					get_opti_path(t_env *env, t_path *path);
int					get_strt_ants(t_env *env, int rounds_cr, int mod_cr);
/*
******************************** If_parsing.c **********************************
*/
int					if_comment(t_env *env, char *line, int opt);
int					if_start_end(t_env *env, char *line);
int					if_ant(t_env *env, char *line);
int					if_room(t_env *env, char *line);
int					if_tunnel(t_env *env, char *line);
int					bfs_time_travel(t_env *env, int index, int dfs_tt);
/*
******************************** reset_or_cpy.c ********************************
*/
int					reset_or_cpy(t_env *env);
/*
************************************ env.c *************************************
*/
t_env				*init_env(t_env *env);
/*
********************************** get_path.c **********************************
*/
int					get_path(t_env *env);
int					get_index(t_env *env, int index, int dfs_tt);
/*
********************************** Add-room.c **********************************
*/
int					add_room_path_tt(t_env *env, t_room *room);
int					add_room_path(t_env *env, t_room *room);
int					add_room_tt(t_env *env, int *intz, int opt);
int					add_room_tt_ret(t_env *env, int *intz, int dfs_tt, int opt);
int					add_room_bfs(t_env *env, int ret);
/*
************************************* dad.c ************************************
*/
int					set_daddy(t_env *env);
void				set_dad(t_env *env, int i, int idx);
void				reset_dad(t_env *env);
/*
****************************** time_travel_2.c *********************************
*/
void				clean_tt(t_env *env, int apply);
int					delete_room_path_tt(t_env *env);
#endif
