/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:11:32 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/25 10:03:09 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*a;
	char	*b;
	int		i;
	int		n;

	a = (char *)dst;
	b = (char *)src;
	i = 0;
	n = len;
	if (dst > src)
	{
		i = n - 1;
		while (i >= 0)
		{
			a[i] = b[i];
			i--;
		}
	}
	else
	{
		dst = ft_memcpy(a, b, len);
	}
	return (dst);
}
