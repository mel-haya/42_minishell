/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:25:47 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/22 05:51:03 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	size_t			i;
	unsigned char	t;

	t = (unsigned char)c;
	i = 0;
	pdst = (unsigned char*)dst;
	psrc = (unsigned char*)src;
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
		if (psrc[i - 1] == t)
			return (pdst + i);
	}
	return (NULL);
}
