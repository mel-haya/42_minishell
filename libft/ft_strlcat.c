/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:10:14 by mhalli            #+#    #+#             */
/*   Updated: 2019/11/30 00:23:55 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t srclenght;
	size_t dstlenght;
	size_t sizetowrite;

	dstlenght = 0;
	srclenght = ft_strlen(src);
	if (dst == NULL && size == 0)
		return (srclenght);
	while (*dst != '\0' && dstlenght < size)
	{
		dst++;
		dstlenght++;
	}
	sizetowrite = size - dstlenght;
	if (sizetowrite == 0)
		return (dstlenght + srclenght);
	while (*src != '\0' && sizetowrite != 1)
	{
		*dst++ = *src++;
		sizetowrite--;
	}
	*dst = '\0';
	return (dstlenght + srclenght);
}
