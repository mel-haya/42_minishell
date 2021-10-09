/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 21:52:06 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/24 22:59:41 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_checkset(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int i;
	int j;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_checkset(s1[i], set))
		i++;
	while (i < j && ft_checkset(s1[j], set))
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
