/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:49:56 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:54:03 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static size_t	count_words(char const *s, char c)
{
	int i;
	int k;

	i = 1;
	k = 1;
	if (!s[0] || s[0] == '\0')
		return (0);
	if (s[0] == c)
		k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i++ - 1] == c)
			k++;
		else
			i++;
	}
	return (k);
}

static char		**malloc_strs(char const *s, char c, char **result)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		if (s[i] == c)
			i++;
		else
		{
			while (!((s[i++]) == c) && s[i])
				k++;
			if (!(result[j] = (char *)malloc(sizeof(char) * (k + 1))))
			{
				while (j >= 0)
					free(result[j--]);
				return (NULL);
			}
			j++;
		}
	}
	return (result);
}

static void		fil_strs(char const *s, char c, char **result)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (!(s[i] == c) && s[i])
				result[j][k++] = s[i++];
			result[j++][k] = '\0';
			k = 0;
		}
	}
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	nb_words;
	char	**result;

	if (s == 0 || c == 0)
		return (NULL);
	nb_words = count_words(s, c);
	if (!(result = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	if (!malloc_strs(s, c, result))
	{
		free(result);
		return (NULL);
	}
	fil_strs(s, c, result);
	result[nb_words] = 0;
	return (result);
}
