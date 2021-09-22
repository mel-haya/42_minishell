/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:29:40 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 08:13:17 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				num;
	char			k;
	unsigned int	i;

	i = 0;
	num = ft_strlen(s);
	k = (char)c;
	while (s[num] != k && num)
		num--;
	if (s[num] == k)
		return ((char *)s + num);
	return (NULL);
}
