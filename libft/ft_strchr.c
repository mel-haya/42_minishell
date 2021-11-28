/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:09:35 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 08:03:05 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			k;

	i = 0;
	k = (char)c;
	while (s[i] != '\0' && s[i] != k)
		i++;
	if (s[i] == k)
		return ((char *)s + i);
	return (NULL);
}
