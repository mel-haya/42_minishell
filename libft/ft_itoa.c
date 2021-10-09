/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 22:10:07 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/19 18:57:37 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_numlen(int num)
{
	int		output;
	long	a;

	if (num == 0)
		return (1);
	a = 1;
	output = 0;
	if (num < 0)
		output++;
	while (num / a)
	{
		output++;
		a *= 10;
	}
	return (output);
}

char		*ft_itoa(int n)
{
	char			*result;
	int				len;
	unsigned int	num;

	len = ft_numlen(n);
	result = malloc(len + 1);
	if (n < 0)
		num = -n;
	else
		num = n;
	if (!result)
		return (NULL);
	result[len] = 0;
	len--;
	while (len >= 0)
	{
		result[len] = num % 10 + 48;
		num /= 10;
		len--;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
