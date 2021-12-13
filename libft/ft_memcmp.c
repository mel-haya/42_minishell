/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 13:44:05 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/06 23:08:16 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int			i;
	unsigned int			result;
	const unsigned char		*p1;
	const unsigned char		*p2;

	i = 0;
	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	result = 0;
	while (n--)
	{
		if (p1[i] != p2[i])
		{
			result = (p1[i] - p2[i]);
			return (result);
		}
		i++;
	}
	return (result);
}
