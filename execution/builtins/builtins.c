/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:05:12 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/10 16:08:23 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(char **cmd)
{
	int		ret;

	ret = 0;
	if (!ft_strncmp(cmd[0], "echo", 5))
		ret = exec_echo(cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		ret = exec_pwd();
	else if (!ft_strncmp(cmd[0], "cd", 3))
		ret = exec_cd(cmd);
	else if (!ft_strncmp(cmd[0], "export", 7))
		ret = exec_export(cmd);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		ret = exec_unset(cmd);
	else if (!ft_strncmp(cmd[0], "env", 4))
		ret = exec_env(cmd);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ret = exec_exit(cmd);
	return (ret);
}
