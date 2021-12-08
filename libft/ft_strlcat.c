/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:10:14 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/06 23:14:42 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclenght;
	size_t	dstlenght;
	size_t	sizetowrite;

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
