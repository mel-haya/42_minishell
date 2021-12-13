/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:17:52 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/11 01:01:25 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd(t_env *env)
{
	char	*oldpwd;
	char	*home;

	if (find_key(env, "HOME") == 0)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	else
	{
		oldpwd = getcwd(NULL, 0);
		change_key_value(env, "OLDPWD", oldpwd);
		home = get_key_value(env, "HOME");
		chdir(home);
		change_key_value(env, "PWD", home);
		return (0);
	}
	return (1);
}

int	exec_cd(char **cmd)
{
	char	*oldpwd;
	char	*cwd;

	if (arr_lenght(cmd) == 1)
		return (cd(g_shell.env));
	else
	{
		oldpwd = getcwd(NULL, 0);
		if (chdir(cmd[1]) == 0)
		{
			change_key_value(g_shell.env, "OLDPWD", oldpwd);
			cwd = getcwd(NULL, 0);
			change_key_value(g_shell.env, "PWD", cwd);
			return (0);
		}
		else
		{
			free(oldpwd);
			cd_err(cmd[0], cmd[1], strerror(errno));
		}
	}
	return (1);
}
