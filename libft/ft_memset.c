/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:10:40 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 08:02:40 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	char			*trr;
	unsigned char	k;

	trr = (char*)b;
	k = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		trr[i] = k;
		i++;
	}
	return (b);
}
