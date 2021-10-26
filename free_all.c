/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourad <mourad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:30:29 by mourad            #+#    #+#             */
/*   Updated: 2021/10/26 16:33:05 by mourad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirection(void)
{
	t_redirection	*red;

	while (g_shell.cmds->redirection)
	{
		red = g_shell.cmds->redirection->next;
		if (g_shell.cmds->redirection->token == '<' && \
		g_shell.cmds->redirection->append)
			unlink(g_shell.cmds->redirection->file);
		free(g_shell.cmds->redirection->file);
		free(g_shell.cmds->redirection);
		g_shell.cmds->redirection = red;
	}
}

void	free_cmds(void)
{
	t_command		*tmp;
	t_redirection	*red;
	int				i;

	while (g_shell.cmds)
	{		
		if ((g_shell.cmds->args))
		{
			i = 0;
			while ((g_shell.cmds->args)[i])
			{
				free((g_shell.cmds->args)[i]);
				i++;
			}
			free(g_shell.cmds->args);
		}
		free_redirection();
		tmp = g_shell.cmds->next;
		free(g_shell.cmds);
		g_shell.cmds = tmp;
	}
}
