/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:30:43 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 08:12:34 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	int				result;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)s2;
	d = (unsigned char *)s1;
	i = 0;
	result = 0;
	while (n-- && (s[i] != '\0' || d[i] != '\0'))
	{
		if (d[i] != s[i] && (s[i] != '\0' || d[i] != '\0'))
		{
			result = (d[i] - s[i]);
			return (result);
		}
		i++;
	}
	return (result);
}
