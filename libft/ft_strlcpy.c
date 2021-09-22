/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 22:32:57 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 08:05:28 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = ft_strlen(src);
	if (size == 0)
		return (i);
	if (dst == NULL)
		return (0);
	if (size && src)
	{
		while (size - 1 > 0 && *src != '\0')
		{
			*dst++ = *src++;
			size--;
		}
	}
	*dst = '\0';
	return (i);
}
