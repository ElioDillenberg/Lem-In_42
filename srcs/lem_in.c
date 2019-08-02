/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/29 19:02:03 by edillenb         ###   ########.fr       */
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

int		set_room_data(char *line, t_room *room, int *command)
{
	if (*command == 1)
	{
		room->start = true;
		*command = 0;
	}
	else
		room->start = false;
	if (*command == 2)
	{
		room->end = true;
		*command = 0;
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
			return (NULL);
	if (!(env->rm_lst_path = (t_room **)ft_memalloc(sizeof(t_room *))))
			return (NULL);
	if (!(env->path = ft_strnew(0)))
			return (NULL);
	env->rm_tab = NULL;
	env->nb_path = 0;
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
		return (free_all(env, -1));
	//view_tunnel_by_name(env);
	ft_printf("\n\n");
	set_max_path(env);
	ft_printf("MAX NBR OF PATH: %d\n", env->max_path);
	/*
	Tant qu on a pqs trouve tous les chemin possible on cherche
	Chaque chemin possede une entree et une sortie disctinct :
	Le chemin 1 va partie de start pour aller a la room A
	Le chemin 2 va partir de staart et aller dans la room B
	Idem pour la sortie
	Actuellemt on recher tous les chemin theoriquemt possible, maais si tu llance big.txt on se rend compte que lq plupart de chemins seront intilisees.
	Donc faudra opti la dessus car c est la partie la plus chronophage de l algo
	 */
	while (env->nb_path < env->max_path)
	{
		//view_tunnel_by_name(env);
		// Parcours des rooms et creation de lien pere - fils
		ft_bfs(env, 0);
		// Extraction du chemin pere fils et destruction des tunnels utilisee
		get_path(env);
		// Reset des rooms
		reset_path_room(env);
		// Si c est le dernier path on ne free pas, la fct free_exit va free
		if (env->nb_path != env->max_path && (*env->rm_lst_path))
			ft_roomdel(env->rm_lst_path);
	}
	// Supprime si il y a des path non valide
	// Puis affiche les path
	if (env->nb_path > 0)
		check_path(env);

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
	return (free_all(env, 0));
}
