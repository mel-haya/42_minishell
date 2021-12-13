/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:27:29 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/06 23:13:01 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*b;
	size_t		i;
	size_t		z;

	i = 0;
	z = ft_strlen(s1);
	b = (char *)malloc(z + 1);
	if (!b)
		return (NULL);
	while (s1[i] != '\0')
	{
		b[i] = (char)s1[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}
