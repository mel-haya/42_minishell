/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:04:18 by mhalli            #+#    #+#             */
/*   Updated: 2019/12/06 04:03:24 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		subst;
	int		size;

	size = 1;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	if (n < 0 && n != -2147483648)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	subst = n;
	while ((subst /= 10) > 0)
		size *= 10;
	subst = n;
	while (size && n != -2147483648)
	{
		ft_putchar_fd((subst / size) + 48, fd);
		subst %= size;
		size /= 10;
	}
}
