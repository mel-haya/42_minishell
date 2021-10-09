/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:50:03 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/20 08:34:52 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*output;

	if (!s)
		return (NULL);
	i = 0;
	output = malloc(ft_strlen(s) + 1);
	if (!output)
		return (NULL);
	while (s[i])
	{
		output[i] = f(i, s[i]);
		i++;
	}
	output[i] = 0;
	return (output);
}
