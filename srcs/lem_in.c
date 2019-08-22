/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/08/12 17:14:14 by edillenb         ###   ########.fr       */
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
	//this can be removed since we dont use path anymore
	if (!(env->path = ft_strnew(0)))
	{
		ft_memdel((void**)env->rm_lst_path);
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
	env->path_tab = NULL;
	env->path_lst[0] = NULL;
	env->path_lst[1] = NULL;
	env->nb_path = 0;
	env->path_i = 0;
	env->rm_tab = NULL;
	env->tu_cut = 0;
	return (env);
}

int			main(int argc, char **argv)
{
	t_env *env;
	int to_find;

	to_find = 1;
	(void)argv;
	env = NULL;
	if (argc > 1)
		return (-1);
	if (!(env = init_env(env)))
		return (-1);
	if ((env->ret = parsing(env)) == -1)
		return (free_all(env, 1, -1));
	ft_putstr(env->to_print);
	//view_tunnel_by_name(env);
	ft_printf("\n\n");
	set_max_path(env);
	ft_printf("MAX NBR OF PATH: %d\n", env->max_path);
	/*
	   Tant qu on a pas trouve tous les chemin possible on cherche
	   Chaque chemin possede une entree et une sortie disctinct :
	   Le chemin 1 va partir de start pour aller a la room A
	   Le chemin 2 va partir de staart et aller dans la room B
	   Idem pour la sortie
	   Actuellemt on recher tous les chemin theoriquemt possible, maais si tu llance big.txt on se rend compte que lq plupart de chemins seront intilisees.
	   Donc faudra opti la dessus car c est la partie la plus chronophage de l algo
	   */
	while (env->nb_path < env->max_path)
	{
//		view_tunnel_by_name(env);
		// Parcours des rooms et creation de lien pere - fils
		if (ft_bfs(env, 0) == -1)
			return (free_all(env, 0, -1));
		// Parcours du tableau de 
		// Extraction du chemin pere fils et on bouche les tunnels utilises
		if (get_path(env) == -1)
			return (free_all(env, 0, -1));
		// if we have detected one or several tunnels to destroy we need to destroy it/them, reset our path and 
		if (env->tu_cut == 1)
			if (cut_and_reset(env) == -1)
				return (free_all(env, 0, -1));
		// Reset des rooms
		reset_path_room(env);
		// Si c est le dernier path on ne free pas, la fct free_exit va free
		if (env->nb_path != env->max_path && (*env->rm_lst_path))
			ft_roomdel(env->rm_lst_path);
		//ICI, FAIRE EN SORTE DE BASCULER SUR LE DEUXIEME ESPACE DE STOCKAGE DE PATHS, EN FONCTION DE CE QUE J'AURAI DECIDE
		// -> pas vraiment enfaite, il faudrait que cette boucle fasse partie d'une autre boucle. qui compare tour a tour:
		// 1 chemin, 2 chemins, 3 chemins, 4 chemins, 5 chemins et ainsi de suite
	}
	// Supprime si il y a des path non valide
	// Puis affiche les path
	if (env->nb_path > 0)
		if (check_path(env) == -1)
			return (free_all(env, 0, -1));
	// Parcours du tableau de path
	int i = 0;
	int j;
	while (i < env->nb_path)
	{
		ft_printf("PATH [%d] : ", i);
		j = 0;
		while (env->path_tab[i][j] != -1)
		{
			ft_printf("[Index : %d | Salle : %s] - ", env->path_tab[i][j], env->rm_tab[env->path_tab[i][j]]->name);
			j++;
		}
		i++;
		ft_printf("\n");
	}
	// A free ou a supprimer c est juste pour afficher les diffrents path
	//	if (check_input(room_lst, nb_ants) == -1)
	//		return (free_room_lst(&room_lst, 1));
	ft_printf("REACHED THE END \n");
	return (free_all(env, 0, 0));
}
