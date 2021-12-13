/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:59:42 by mel-haya          #+#    #+#             */
/*   Updated: 2021/12/11 23:59:45 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_err(char *msg, char *output, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(msg, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(output, fd);
}

void	export_err(char *cmd, char *identifier)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	cd_err(char *cmd, char *path, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}
