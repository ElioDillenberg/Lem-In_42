/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_multi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:12:43 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/11 19:56:52 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

/*
** this block returns the trimmed 1st line and reallocates for the leftover
*/

char	*trim_to_eol(char **str)
{
	char	*result;
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len])
		len++;
	i = ft_strlen(*str) - len;
	if (!(result = ft_strsub((const char**)str, 0, len, 0)))
		return (NULL);
	if (!(new_str = ft_strsub((const char**)str, len + 1, i, 0)))
		return (NULL);
	free(*str);
	*str = new_str;
	return (result);
}

/*
** Create a new node, give it FD as a key, gives it a string as content
*/

t_node	*ft_newnode(char const *str, size_t str_size, int fd)
{
	t_node	*new_elem;

	if (!(new_elem = (t_node*)malloc(sizeof(t_node))))
		return (NULL);
	if (!str)
	{
		new_elem->str_size = 0;
		new_elem->str = NULL;
	}
	else
	{
		if (!(new_elem->str = (char*)malloc(sizeof(str_size))))
		{
			free(new_elem);
			new_elem = NULL;
			return (NULL);
		}
		ft_memcpy(new_elem->str, str, str_size);
		new_elem->str_size = str_size;
		new_elem->key = fd;
	}
	new_elem->next = NULL;
	return (new_elem);
}

/*
** LF fd key among list, if foudn returns pointer to it, else creates new node
*/

t_node	*lf_k(t_node **head, int fd)
{
	t_node	*new_box;

	new_box = *head;
	while (new_box != NULL)
	{
		if (fd == new_box->key)
			return (new_box);
		new_box = new_box->next;
	}
	if (!(new_box = ft_newnode("\0", 1, fd)))
		return (NULL);
	new_box->next = *head;
	*head = new_box;
	return (new_box);
}

/*
** free current node, links previous node to next
*/

void	del_node(t_node **head, int fd)
{
	t_node	*prev;
	t_node	*current;

	prev = *head;
	current = *head;
	if (current == NULL)
		return ;
	if (current && current->key == fd)
	{
		*head = current->next;
		free(current);
		current = NULL;
		return ;
	}
	while (current != NULL && current->key != fd)
	{
		prev = current;
		current = current->next;
	}
	prev->next = current->next;
	free(current);
	current = NULL;
}

/*
** changes line to a pointer to the next line found within of reading FD
*/

int		get_next_line_multi(const int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static t_node	*head = NULL;
	t_node			*box;
	char			*temp;

	if (!line || fd < 0 || fd > OM || BUFF_SIZE < 1 || !(box = lf_k(&head, fd)))
		return (-1);
	while (!(ft_strchr(box->str, '\n')) && (ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (ret == -1 || !(temp = ft_strjoin(box->str, buf)))
			return (-1);
		free(box->str);
		box->str = temp;
	}
	if (ret == 0 && ft_strlen(box->str) == 0)
		return (0);
	if (!(*line = trim_to_eol(&(box->str))))
		return (-1);
	if (ret == 0 && ft_strlen(box->str) == 0)
		del_node(&head, fd);
	return (1);
}
