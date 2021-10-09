/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:16:35 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/27 15:45:12 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	int		len;
	char	*pdst;
	char	*psrc;

	if (!dst && !src)
		return (0);
	pdst = (char*)dst;
	psrc = (char*)src;
	i = 0;
	len = n;
	while (i < len)
	{
		if (pdst[i] != psrc[i])
			pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}
