/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:24:37 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 16:24:39 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	open_file(char *f, t_redirection *tmp)
{
	int	file;

	if (tmp->token == '>' && !tmp->append)
		file = open(f, O_WRONLY | O_TRUNC);
	else if (tmp->token == '>' && tmp->append)
		file = open(f, O_WRONLY | O_APPEND, 0644);
	else if (tmp->token == '<')
		file = open(f, O_RDONLY);
	return (file);
}

void	exec_redir(t_redirection *redir)
{
	t_redirection	*tmp;
	int				file;

	tmp = redir;
	while (tmp)
	{
		file = open_file(redir->file, tmp);
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
}

void	redir_exec(t_command *cmd)
{
	char	*err_msg;
	int		fds[2];

	if (filter_redir(cmd->redirection))
	{
		err_msg = path_case_error();
		fds_saver(fds, 0);
		exec_redir(cmd->redirection);
		if (is_builtin(cmd->args[0]) == 1)
			exec_builtin(cmd->args);
		else if (!is_builtin(cmd->args[0]))
			exec_cmd(get_path(), cmd->args, err_msg);
		fds_saver(fds, 1);
		free(err_msg);
	}
}
