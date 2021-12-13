/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:01:59 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/11 23:55:39 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
	}
	free(arr);
}

void	execution(void)
{
	if (!g_shell.cmds->next && !g_shell.cmds->redirection)
		command_exec(g_shell.cmds);
	else if (!g_shell.cmds->next && g_shell.cmds->redirection)
		redir_exec(g_shell.cmds);
	else if (g_shell.cmds->next)
		pipes(-1);
}
