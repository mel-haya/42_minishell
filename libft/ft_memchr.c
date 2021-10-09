/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:34:05 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/21 23:41:13 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	int		i;
	int		len;

	len = n;
	str = (char *)s;
	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}
