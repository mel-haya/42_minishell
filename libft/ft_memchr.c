/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:33:19 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 07:54:14 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	unsigned char	k;
	unsigned int	i;
	unsigned char	*v;

	v = (unsigned char *)s;
	i = 0;
	k = (unsigned char)c;
	while (i < len)
	{
		if (v[i] == k)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
