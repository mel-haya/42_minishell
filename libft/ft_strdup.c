/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:27:29 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 08:04:38 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char		*b;
	size_t		i;
	size_t		z;

	i = 0;
	z = ft_strlen(s1);
	if (!(b = (char *)malloc(z + 1)))
		return (NULL);
	while (s1[i] != '\0')
	{
		b[i] = (char)s1[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}
