/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:26:24 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 14:26:27 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_nbr(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_int(char *str)
{
	int		nbr;
	int		nbr_len;

	nbr = 0;
	nbr_len = ft_strlen(str) - 1;
	if (ft_strncmp(str, "-1", nbr_len))
	{
		nbr = ft_atoi(str);
		if (nbr == -1)
			return (0);
	}
	return (1);
}

int	exit_error(char *cmdName)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmdName, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (255);
}

void	exec_exit(char **cmd)
{
	if (cmd[1] && cmd[2] == NULL)
	{
		if (!is_int(cmd[1]) || !is_nbr(cmd[1]))
			exit(exit_error(cmd[1]));
		else
		{
			ft_putendl_fd("exit", 1);
			exit(ft_atoi(cmd[1]));
		}
	}
	else if (cmd[1] == NULL)
	{
		ft_putendl_fd("exit", 1);
		exit (0);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
}
