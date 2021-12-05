/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:20:36 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/05 04:33:03 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	dup_fds(t_command *cmd, int fds[2], int input_fd)
{
	if (cmd->is_piped == 0 && cmd->next && cmd->next->is_piped == 1)
	{
		dup2(g_shell._savein, STDIN_FILENO);
		dup2(fds[1], 1);
	}
	else if (cmd->is_piped == 1 && cmd->next && cmd->next->is_piped == 1)
	{
		dup2(input_fd, 0);
		dup2(fds[1], 1);
	}
	else
		dup2(input_fd, 0);
}

void	execute_pipcmd(t_command *cmd)
{
	if (cmd && !cmd->redirection)
		command_exec(cmd);
	else
		redir_exec(cmd);
}

void	duper(t_command *cmd, int fds[2], int input_fd)
{
	dup_fds(cmd, fds, input_fd);
	close(fds[0]);
	close(fds[1]);
	close(input_fd);
	execute_pipcmd(cmd);
	exit(1);
}

int	save_input_fd(t_command *cmd, int fds[2], int input_fd)
{
	close(fds[1]);
	close(input_fd);
	input_fd = fds[0];
	if (cmd->next == NULL)
		close(fds[0]);
	return (input_fd);
}

void	pipes(void)
{
	t_command	*tmp;
	int			fds[2];
	int			pid;
	int			intput_fd;

	intput_fd = -1;
	tmp = g_shell.cmds;
	g_shell.is_forked = 1;
	while (tmp)
	{
		pipe(fds);
		pid = fork();
		if (pid == 0)
			duper(tmp, fds, intput_fd);
		intput_fd = save_input_fd(tmp, fds, intput_fd);
		dup2(g_shell._savein, STDIN_FILENO);
		dup2(g_shell._saveout, STDOUT_FILENO);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	while (wait(&pid) != -1)
		;
}
