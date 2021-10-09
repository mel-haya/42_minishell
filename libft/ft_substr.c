/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:28:50 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/22 06:09:38 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;
	int		n;

	if (!s)
		return (NULL);
	n = len;
	i = 0;
	if (start > ft_strlen(s))
		n = 0;
	sub = malloc(n + 1);
	if (!sub)
		return (NULL);
	while (i < n)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}
