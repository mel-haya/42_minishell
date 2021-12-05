/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:05:12 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 16:05:13 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	exec_builtin(char **cmd)
{
	int		ret;

	if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
		ret = exec_echo(cmd);
	else if (!ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])))
		ret = exec_pwd();
	else if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
		ret = exec_cd(cmd);
	else if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
		ret = exec_export(cmd);
	else if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
		ret = exec_unset(cmd);
	else if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
		ret = exec_env(cmd);
	else if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
		exec_exit(cmd);
	return (ret);
}
