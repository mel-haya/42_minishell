/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:17:52 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 14:17:54 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	cd(t_env *env)
{
	char	*oldpwd;
	char	*home;

	if (find_key(env, "HOME") == 0)
		printf("minishell: cd: HOME not set\n");
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
			printf("minishell: %s: %s: %s\n", cmd[0], cmd[1], strerror(errno));
	}
	return (1);
}
