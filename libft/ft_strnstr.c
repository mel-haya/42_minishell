/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:23:41 by mhalli            #+#    #+#             */
/*   Updated: 2019/11/30 01:23:34 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlelenght;
	size_t	ptrtoneedle;

	ptrtoneedle = 0;
	needlelenght = ft_strlen(needle);
	if ((!*needle && !len) || !*needle)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	if (ft_strlen(haystack) < needlelenght)
		return (NULL);
	while (ptrtoneedle <= len)
	{
		if (!(ft_strncmp((haystack + ptrtoneedle), needle, needlelenght)))
			return ((char *)haystack + ptrtoneedle);
		ptrtoneedle++;
		len--;
	}
	return (NULL);
}
