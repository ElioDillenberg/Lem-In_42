/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 12:35:39 by thallot           #+#    #+#             */
/*   Updated: 2019/08/13 17:38:16 by edillenb         ###   ########.fr       */
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
   On ajoute structure t_path contenant l'index de la room a ajouter a notre path
   */

int		add_path_index(t_path **path, int index, t_env *env)
{
	t_path	*new;

	if (!(new = (t_path*)malloc(sizeof(t_path))))
		return (-1);
	new->index = index;
	if (*path == NULL)
	{
		*path = new;
		new->len = 0;
		new->nb = env->nb_path;
		new->next_room = NULL;
		new->next_path = NULL;
	}
	else
	{
		new->next_room = *path;
		new->next_path = NULL;
		*path = new;
		new->len = new->next_room->len + 1;
		new->nb = new->next_room->nb;
		new->next_room->nb = 0;
		new->next_room->len = 0;
	}
	return (0);
}

/*
   On ajoute le path trouve a notre liste de paths
   */

void	add_path_lst(t_env *env, t_path *path)
{
	t_path	*cr;
	int		i;

	i = 1;
	cr = env->path_lst[env->cr_path];
	if (env->path_lst[env->cr_path] == NULL)
	{
		path->nb = i;
		env->path_lst[env->cr_path] = path;
	}
	else
	{
		i++;
		while (cr->next_path != NULL)
		{
			cr = cr->next_path;
			i++;
		}
		cr->next_path = path;
		path->nb = i;
	}
}

/*
   Parcours de graphe en largeur, cf BFS. Pour chaque enfant,
   son parent est spécifié dans room->parent pour ensuite recreer le chemin
   */

int		ft_bfs(t_env *env, int start)
{
	int i;
	int index;
	t_room	*tmp;

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
			if (env->tu_tab[index][i] == 1 && env->rm_tab[i]->path == 0 && i != 0)
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
			env->nb_path++;
			return (0);
		}
		// Si on a trouve la room end on incremente le nb de path trouve
		if ((*env->rm_lst_path)->end)
			env->nb_path++;
	}
	tmp = (*env->rm_lst_path);
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
	t_path	*path;
	t_path	*cr;
	
	path = NULL;
	cr = NULL;
	//On prends l index de la case end et on cherche son pere
	index = env->nt_rm[1] - 1;
	parent = env->rm_tab[index]->parent;
	if (add_path_index(&path, index, env) == -1)
		return (-1);
	while (env->rm_tab[index]->parent != -1)
	{
		save = index;
		parent = env->rm_tab[index]->parent;
		index = env->rm_tab[parent]->index;
		//on considere tu_tab[save][index] comme le tunnel allant DE save A index
		//on decide de mettre la case du tableau qui vient d'etre prise a -1 ou a -2, en fonction de si le chemin dans le sens inverse est a 1 ou a -1
		env->tu_tab[index][save] = env->tu_tab[save][index] == -1 ? -2 : -1;
		if (env->tu_tab[save][index] == -1)
		{
			env->tu_tab[index][save] = -2;
			env->tu_tab[save][index] = -2;
			env->tu_cut = 1;
		}
		else
			env->tu_tab[index][save] = -1;
		if (add_path_index(&path, index, env) == -1)
			return (-1);
	}
	add_path_lst(env, path);
	return (0);
}
