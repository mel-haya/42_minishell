/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:19:48 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/25 09:21:30 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *word, size_t n)
{
	int	i;
	int j;
	int num;

	num = n;
	i = -1;
	if (!n && ft_strlen(word))
		return (NULL);
	if (!ft_strlen(word) || !word)
		return ((char *)str);
	while (str[++i] != 0 && i < num)
	{
		j = 0;
		while (i + j - 1 < num)
		{
			if (word[j] == '\0')
				return ((char *)str + i);
			else if (str[i + j] == word[j])
				j++;
			else
				break ;
		}
	}
	return (NULL);
}
