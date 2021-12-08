/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 03:51:30 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/06 23:12:17 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	howmanyword(const char *s, char c)
{
	int		key;
	int		words;

	key = 0;
	words = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			key = 0;
		else if (key == 0)
		{
			key = 1;
			words++;
		}
		s++;
	}
	return (words);
}

static void	*frree(char **tab, int j)
{
	while (j--)
		free(tab[j]);
	free(tab);
	return (NULL);
}

static int	wordlenght(const char *s, char c, int i)
{
	int		lenght;

	lenght = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		lenght++;
	}
	return (lenght);
}

static char	**dotherest(const char *s, char c, char **tab)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	while (s[i] && j < howmanyword(s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		tab[j] = malloc(sizeof(char ) * (wordlenght(s, c, i) + 1));
		if (tab[j] == NULL)
			return (frree(tab, j));
		while (s[i] != c && s[i] != '\0')
			tab[j][k++] = s[i++];
		tab[j][k] = '\0';
		j++;
	}
	tab[howmanyword(s, c)] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(8 * (howmanyword(s, c) + 1));
	if (!tab)
		return (NULL);
	return (dotherest(s, c, tab));
}
