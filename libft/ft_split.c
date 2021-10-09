/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 04:38:19 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/24 22:17:36 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *str, char c)
{
	int i;
	int output;

	i = 0;
	output = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
		{
			output++;
			i++;
		}
		else
			i++;
	}
	return (output);
}

static int	ft_letter_count(char const *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != c && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

static void	ft_free(char **p, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(*(p + i));
		i++;
	}
	free(p);
}

static char	*ft_get_word(char const *str, char ch)
{
	int		i;
	char	*c;

	i = 0;
	c = malloc(ft_letter_count(str, ch) + 1);
	if (!c)
		return (NULL);
	while (str[i] != ch && str[i])
	{
		c[i] = str[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char		**ft_split(char const *str, char c)
{
	char	**array;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!str)
		return (NULL);
	array = malloc(sizeof(char*) * (ft_word_count(str, c) + 1));
	if (!array)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
		{
			if (!(array[k] = ft_get_word(&str[i], c)))
				ft_free(array, k);
			k++;
		}
		i++;
	}
	array[ft_word_count(str, c)] = 0;
	return (array);
}
