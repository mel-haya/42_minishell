/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 19:51:16 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 08:00:31 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	char		*dlen;
	const char	*slen;

	d = (char *)dst;
	s = (const char *)src;
	dlen = d + (len - 1);
	slen = s + (len - 1);
	if (s == NULL && d == NULL)
		return (NULL);
	if (d < s || (d == s && len == 1))
		return (ft_memcpy(d, s, len));
	while (len-- > 0)
	{
		*dlen-- = *slen--;
	}
	return (dst);
}
