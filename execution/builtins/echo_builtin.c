/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:19:36 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 14:19:39 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_option(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[i] == '-' && ft_strlen(cmd) > 1)
	{
		i++;
		while (cmd[i])
		{
			if (cmd[i] != 'n')
				return (0);
			i++;
		}
	}
	return (i);
}

int	toprint(char **cmd, int option)
{
	int		i;

	i = 1;
	while (option && cmd[i])
	{
		if (!is_option(cmd[i]))
			return (i);
		i++;
	}
	return (i);
}

int	exec_echo(char **cmd)
{
	int		option;
	int		index;

	if (arr_lenght(cmd) > 1)
	{
		option = is_option(cmd[1]);
		index = toprint(cmd, option);
		while (cmd[index])
		{
			ft_putstr_fd(cmd[index], 1);
			if (cmd[index + 1] != NULL)
				ft_putstr_fd(" ", 1);
			index++;
		}
		if (!option)
			ft_putchar_fd('\n', 1);
	}
	else
		ft_putchar_fd('\n', 1);
	return (0);
}
