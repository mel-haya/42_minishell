/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:09:21 by mourad            #+#    #+#             */
/*   Updated: 2021/12/10 03:06:52 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *envp, int i)
{
	char	*str;

	if (!envp[i])
		return (NULL);
	str = ft_strdup(envp + i);
	if (!str)
		exit_malloc_fail();
	ft_strlcpy(str, envp + i + 1, ft_strlen(envp) - i);
	return (str);
}

void	aloc_red(t_command *cmd, t_redirection	**tmp)
{
	if (!cmd->redirection)
	{
		cmd->redirection = malloc(sizeof(t_redirection));
		if (!(cmd->redirection))
			exit_malloc_fail();
		*tmp = cmd->redirection;
	}
	else
	{
		(*tmp)->next = malloc(sizeof(t_redirection));
		if (!((*tmp)->next))
			exit_malloc_fail();
		*tmp = (*tmp)->next;
	}
}

int	init_global(void)
{
	g_shell.env = malloc(sizeof(t_env));
	g_shell.is_forked = 0;
	if (!g_shell.env)
		exit_malloc_fail();
	g_shell.status = 0;
	ignctl();
	return (0);
}
