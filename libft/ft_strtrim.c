/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 02:20:09 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 08:17:52 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_trim1(const char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0' && ft_strchr(s2, s1[i]))
	{
		i++;
	}
	return (i);
}

int		ft_trim2(const char *s1, const char *s2)
{
	int		i;

	i = ft_strlen(s1);
	if (!s1 || !s2)
		return (0);
	while (ft_strrchr(s2, s1[i - 1]))
	{
		i--;
		if (i == 0)
			return (0);
	}
	return (i);
}

char	*error(int f, int s, char const *s1)
{
	char	*b;

	if (f > 1)
	{
		if (!(b = (char *)malloc(sizeof(char) * f)))
			return (NULL);
		ft_strlcpy(b, s1 + s, f);
	}
	else
	{
		if (!(b = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		b[0] = 0;
	}
	return (b);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s;
	int		f;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup((char *)s1));
	s = ft_trim1(s1, set);
	f = ft_trim2(s1, set);
	f = f - s + 1;
	return (error(f, s, s1));
}
