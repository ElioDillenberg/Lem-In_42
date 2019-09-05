/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/08/31 15:48:36 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

/*
 ** This function parses the input found in line
 ** It then activates flags within the node depending on found type ->
 */

int		set_room_data(char *line, t_room *room, int *start_end)
{
	if (start_end[0] == 1)
	{
		room->start = true;
		start_end[0] = 2;
	}
	else
		room->start = false;
	if (start_end[1] == 1)
	{
		room->end = true;
		start_end[1] = 2;
	}
	else
		room->end = false;
	room->ant_here = false;
	room->ant = 0;
	room->parent = -1;
	room->next = NULL;
	if (get_room(line, room) == -1)
		return (-1);
	return (0);
}

/*
 ** One way to optimize parsing here would be to add room at the beginning of
 ** the list and not at the end.
 */

int			add_room(char *line, t_room **head, int *command)
{
	t_room 	*new_room;
	t_room 	*last;

	last = *head;
	if (!(new_room = (t_room*)ft_memalloc(sizeof(t_room))))
		return (free_room_lst(head, -1));
	if (set_room_data(line, new_room, command) == -1)
		return (free_room_lst(head, -1));
	if (*head == NULL)
	{
		*head = new_room;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_room;
	return (0);
}

t_env *init_env(t_env *env)
{
	int j;

	j = 0;
	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		return (NULL);
	if (!(env->rm_lst = (t_room **)ft_memalloc(sizeof(t_room *))))
	{
		ft_memdel((void**)&env);
		return (NULL);
	}
	if (!(env->rm_lst_path = (t_room **)ft_memalloc(sizeof(t_room *))))
	{
		ft_memdel((void**)env->rm_lst);
		ft_memdel((void**)&env);
		return (NULL);
	}
	if (!(env->path_lst = (t_path**)ft_memalloc(sizeof(t_path*) * 2)))
	{
		ft_memdel((void**)env->rm_lst_path);
		ft_memdel((void**)env->rm_lst);
		ft_memdel((void**)&env);
		return (NULL);
	}
	if (!(env->map = ft_strnew(0)))
		return (NULL);
	env->path_tab = NULL;
	env->path_lst[0] = NULL;
	env->path_lst[1] = NULL;
	env->nb_path = 0;
	env->rm_tab = NULL;
	env->tu_cut = 0;
	env->lf_path = 0;
	env->cr_path = 0;
	env->ants_end = 0;
	env->next_ant = 1;
	env->map_len = 0;
	env->round = 0;
	env->mod_ants = 0;
	env->total_rounds = 0;
	env->opt_rounds = 0;
	env->opt_paths = 0;
	env->opt_file_path = NULL;
	env->opt_turn = 0;
	return (env);
}

int			main(int argc, char **argv)
{
	t_env *env;
	int to_find;

	to_find = 1;
	(void)argv;
	env = NULL;
	if (!(env = init_env(env)))
		return (-1);
	if (argc > 1)
		if (get_option(env, argv) == -1)
			return (free_all(env, 0, 0));
	if ((env->ret = parsing(env)) == -1)
		return (free_all(env, 1, -1));
	ft_putstr(env->map);
	// ft_printf("\n\n");
	set_max_path(env);
	if (env->max_path == 0)
		return(free_all(env, 0, 0));
	// ft_printf("MAX NBR OF PATH: %d\n", env->max_path);
	// t_path	*cr_path_print = env->path_lst[0];
	// t_path	*cr_room_print = NULL;
	/*
	   Tant qu on a pas trouve tous les chemins possible on cherche
	   Chaque chemin possede une entree et une sortie disctinct :
	   Le chemin 1 va partir de start pour aller a la room A
	   Le chemin 2 va partir de staart et aller dans la room B
	   Idem pour la sortie
	   Actuellemt on recher tous les chemin theoriquemt possible, maais si tu llance big.txt on se rend compte que lq plupart de chemins seront intilisees.
	   Donc faudra opti la dessus car c est la partie la plus chronophage de l algo
	   */
	while (env->lf_path < env->max_path)
	{
		env->lf_path++;
		// ft_printf("----------\nlf_path = %d\n", env->lf_path);
		env->nb_path = 0;
		while (env->nb_path < env->lf_path)
		{
			// Parcours des rooms et creation de lien pere - fils
			if (ft_bfs(env, 0) == -1)
				return (free_all(env, 0, -1));
			// Parcours du tableau de
			// Extraction du chemin pere fils et on bouche les tunnels utilises
			if (get_path(env) == -1)
				return (free_all(env, 0, -1));
			// if we have detected one or several tunnels to destroy we need to destroy it/them, reset our path and
			if (env->tu_cut == 1)
				cut_and_reset(env, 1);
			// Reset des rooms
			reset_path_room(env);
			// Si c est le dernier path on ne free pas, la fct free_exit va free
			if (env->nb_path != env->max_path && (*env->rm_lst_path))
				ft_roomdel(env->rm_lst_path);
		}
		// cr_path_print = env->path_lst[0];
		// cr_room_print = NULL;
		// // ft_printf("PATH_LST 0 : \n");
		// while (cr_path_print != NULL)
		// {
		// 	// ft_printf("PATH [%d] (len = %d) : ", cr_path_print->nb, cr_path_print->len);
		// 	cr_room_print = cr_path_print;
		// 	while (cr_room_print != NULL)
		// 	{
		// 		ft_printf("[Index : %d | Salle : %s] - ", cr_room_print->index, env->rm_tab[cr_room_print->index]->name);
		// 		cr_room_print = cr_room_print->next_room;
		// 	}
		// 	cr_path_print = cr_path_print->next_path;
		// 	ft_printf("\n");
		// }
		// ft_printf("\n");
		// ft_printf("PATH_LST 1 : \n");
		// cr_path_print = env->path_lst[1];
		// cr_room_print = NULL;
		// while (cr_path_print != NULL)
		// {
		// 	// ft_printf("PATH [%d] (len = %d) : ", cr_path_print->nb, cr_path_print->len);
		// 	cr_room_print = cr_path_print;
		// 	while (cr_room_print != NULL)
		// 	{
		// 		// ft_printf("[Index : %d | Salle : %s] - ", cr_room_print->index, env->rm_tab[cr_room_print->index]->name);
		// 		cr_room_print = cr_room_print->next_room;
		// 	}
		// 	cr_path_print = cr_path_print->next_path;
		// 	// ft_printf("\n");
		// }
		// // ft_printf("\n");
		if (env->lf_path > 1)
		{
			// ft_printf("Chemin opti : %d\n", get_opti_path(env));
			// ft_printf("env->cr_path = %d\n", env->cr_path);
			if (get_opti_path(env) != env->cr_path)
			{
				// ft_printf("ON BREAK MAINTENANT!!!\n");
				if (env->lf_path > 2)
				env->cr_path = env->cr_path == 0 ? 1 : 0;
				break ;
			}
			else
			{
			// ft_printf("ON DOIT EFFACER LE PRECEDENT ET RELANCER BFS FRAIS\n");
			ft_path_lst_del(&(env->path_lst[env->cr_path == 0 ? 1 : 0]));
			env->path_lst[env->cr_path == 0 ? 1 : 0] = NULL;
			}
		}
		cut_and_reset(env, 0);
		reset_path_room(env);
		env->cr_path = env->cr_path == 0 ? 1 : 0;
		// ft_printf("----------\n");
	}
	reset_buffer(env);
	//write(1, env->map, env->map_len);
	result(env);
	if (env->round)
		ft_printf("[ROUNDS : %d]\n", env->total_rounds);
	ft_printf("NBR PATH %d\n", env->nb_path);
	ft_memdel((void **)&(env)->map);
	return (free_all(env, 0, 0));
}
