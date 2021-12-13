/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:24:37 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/10 16:09:07 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *f, t_redirection *tmp)
{
	int	file;

	file = -1;
	if (tmp->token == '>' && !tmp->append)
		file = open(f, O_WRONLY | O_TRUNC);
	else if (tmp->token == '>' && tmp->append)
		file = open(f, O_WRONLY | O_APPEND, 0644);
	else if (tmp->token == '<')
		file = open(f, O_RDONLY);
	return (file);
}

int	exec_redir(t_redirection *redir)
{
	t_redirection	*tmp;
	int				file;

	tmp = redir;
	while (tmp)
	{
		file = open_file(tmp->file, tmp);
		if (tmp->token == '>' && !tmp->append)
			dup2(file, 1);
		else if (tmp->token == '>' && tmp->append)
			dup2(file, 1);
		else if (tmp->token == '<')
			dup2(file, 0);
		close(file);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (0);
}

void	redir_exec(t_command *cmd)
{
	char	*err_msg;
	int		fds[2];
	char	*path;

	path = NULL;
	if (filter_redir(cmd->redirection))
	{
		path = get_path();
		err_msg = path_case_error();
		fds_saver(fds, 0);
		g_shell.status = exec_redir(cmd->redirection);
		if (is_builtin(cmd->args[0]) == 1)
			g_shell.status = exec_builtin(cmd->args);
		else if (!is_builtin(cmd->args[0]))
			exec_cmd(path, cmd->args, err_msg);
		fds_saver(fds, 1);
		free(err_msg);
		free(path);
	}
}
