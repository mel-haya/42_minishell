/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:09:21 by mourad            #+#    #+#             */
/*   Updated: 2021/12/03 11:07:45 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aloc_red(t_command *cmd, t_redirection	**tmp)
{
	if (!cmd->redirection)
	{
		cmd->redirection = malloc(sizeof(t_redirection));
		*tmp = cmd->redirection;
	}
	else
	{
		(*tmp)->next = malloc(sizeof(t_redirection));
		*tmp = (*tmp)->next;
	}
}

int	init_global(void)
{
	g_shell.env = malloc(sizeof(t_env));
	g_shell.is_forked = 0;
	if (!g_shell.env || !g_shell.cmds)
		return (1);
	g_shell.status = 0;
	ignctl();
	return (0);
}
