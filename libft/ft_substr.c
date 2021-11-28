/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 22:56:16 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 08:15:53 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*b;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > len)
		return (ft_strdup(""));
	if (!(b = (char *)malloc(len + 1)))
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		b[i] = s[start + i];
		i++;
	}
	b[i] = '\0';
	return (b);
}
