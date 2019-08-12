/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 12:35:39 by thallot           #+#    #+#             */
/*   Updated: 2019/08/12 17:35:58 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

/*
   Reset les parent et les path (variable qui definis si une case a ete explorée )
   pour relancer bfs et trouver un nouveau Parcours
   */
void reset_path_room(t_env *env)
{
	int i;

	i = 0;
	while (i < env->nt_rm[1])
	{
		env->rm_tab[i]->path = 0;
		env->rm_tab[i]->parent = -1;
		i++;
	}
}

/*
   Ajout d'une room dans env->rm_lst_path
   */

int			add_room_path(t_env *env, t_room *room)
{
	t_room 	*new_room;
	t_room 	*last;

	last = *(env->rm_lst_path);
	if (!(new_room = (t_room*)ft_memalloc(sizeof(t_room))))
		return (-1);
	if (!(new_room->name = ft_strdup(room->name)))
	{
		ft_memdel((void**)&new_room);
		return (-1);
	}
	new_room->index = room->index;
	new_room->parent = room->parent;
	new_room->end = room->end;
	if (*(env->rm_lst_path) == NULL)
	{
		*(env->rm_lst_path) = new_room;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_room;
	return (0);
}

/*
   Suppression de la premiere room dans env->rm_lst_path
   */

int			delete_room_path(t_env *env)
{
	t_room 	*room;

	room = *env->rm_lst_path;
	*env->rm_lst_path = (*env->rm_lst_path)->next;
	ft_roomdelone(&room);
	return (0);
}

/*
   Parcours de graphe en largeur, cf BFS. Pour chaque enfant,
   son parent est spécifié dans room->parent pour ensuite recreer le chemin
   */

int		ft_bfs(t_env *env, int start)
{
	int i;
	int index;

	// ajout de la room start a la liste
	if (add_room_path(env, env->rm_tab[start]) == -1)
		return (-1);
	// Parcours du graphe jusqu a trouver la room de sortie
	while (*env->rm_lst_path && !(*env->rm_lst_path)->end)
	{
		i = 0;
		// On prends l index de start et on la supprime de la liste
		index = (*env->rm_lst_path)->index;
		delete_room_path(env);
		while (i < env->nt_rm[1])
		{
			if (env->tu_tab[i][index] == 1 && env->rm_tab[i]->path == 0 && i != 0)
			{
				// Si une connection a ete trouve avec une autre room on renseigne son parent, on marque que la case a ete explorer et on l add a la liste
				env->rm_tab[i]->path = 1;
				env->rm_tab[i]->parent = index;
				if (add_room_path(env, env->rm_tab[i]) == -1)
					return (-1);
			}
			i++;
		}
		// Si toutes les room sont parcourus sans trouve la room end on ne trouvera plus dautre chemin
		if (!(*env->rm_lst_path))
		{
			env->max_path = env->nb_path;
			return (0);
		}

		// Si on a trouve la room end on incremente le nb de path trouve
		if ((*env->rm_lst_path)->end)
			env->nb_path++;
	}
	return (0);
}

/* Parcours la graphe en commencant par la fin, et en remontant par le parent de chaque rooms
   le path est un char *, où les rooms sont renseignées par leurs id, et delimieter par un espace

   Puis on supprime les tunnels de notre path pour essayer de trouver un nouveau chemin
   Chaque path commence par la room start, et fini par un "|"
   */

int		get_path(t_env *env)
{
	int parent;
	int index;
	int save;
	char *tmp;

	//On prends l index de la case end et on cherche son pere
	index = env->nt_rm[1] - 1;
	parent = env->rm_tab[index]->parent;
	// On join son nom dans le path suivis d un espace pour delimiter
	if (!(tmp = ft_strrev(ft_itoa(index))))
		return (-1);
	if (!(env->path = ft_strrev(env->path)))
	{
		ft_memdel((void**)&tmp);
		return (-1);
	}
	if (!(env->path = ft_joinfree(env->path, "|")))
	{
		ft_memdel((void**)&tmp);
		return (-1);
	}
	if (!(env->path = ft_joinfree(env->path, tmp)))
	{
		ft_memdel((void**)&tmp);
		return (-1);
	}
	if (!(env->path = ft_joinfree(env->path, " ")))
	{
		ft_memdel((void**)&tmp);
		return (-1);
	}
	ft_memdel((void **)&tmp);
	// Tant qu on est pas sur la case start (qui na pas de pere ;( ) on continue)
	while (env->rm_tab[index]->parent != -1)
	{
		save = index;
		parent = env->rm_tab[index]->parent;
		index = env->rm_tab[parent]->index;
		env->tu_tab[save][index] = 0;
		env->tu_tab[index][save] = 0;
		if (!(tmp = ft_strrev(ft_itoa(index))))
			return (-1);
		if (!(env->path = ft_joinfree(env->path, tmp)))
		{
			ft_memdel((void**)&tmp);
			return (-1);
		}
		ft_memdel((void **)&tmp);
		if (env->rm_tab[index]->parent != -1)
			if (!(env->path = ft_joinfree(env->path, " ")))
				return (-1);
	}
	env->path = ft_strrev(env->path);
	return (0);
}
