#include "execution.h"

void	dup_fds(t_command *cmd, int fds[2], int input_fd)
{
	// the first command won't be piped && the next one will be
	// we should output on the fd[1] , input fd stay the same
	if (cmd->is_piped == 0 && cmd->next && cmd->next->is_piped == 1)
		dup2(fds[1], 1);
	// cmd is piped and the next one too this means that we are one the middles command
	// so we should read from the input fd && output on fd[1]
	else if (cmd->is_piped == 1 && cmd->next && cmd->next->is_piped == 1)
	{
		dup2(input_fd, 0);
		dup2(fds[1], 1);
	}
	// if the cmd is piped and there is no others cmds so its the last one
	// we should read from the input fd and output on the normal stdout
	else
		dup2(input_fd, 0);
}

void	execute_pipcmd(t_command *cmd)
{
	// if (!cmd->next && !cmd->redirection)
	command_exec(g_shell.env, cmd);
	// else if (!cmd->next && cmd->redirection)
	// 	redir_exec();
}

void	duper(t_command *cmd, int fds[2], int input_fd)
{
	dup_fds(cmd, fds, input_fd);
	close(fds[0]);
	close(fds[1]);
	close(input_fd);
	//then exec the cmd and kill child process
	execute_pipcmd(cmd);
	exit(1);
}

int		save_input_fd(t_command *cmd, int fds[2], int input_fd)
{
	// close all the fds we are done using
	close(fds[1]);
	// close saved input fd only in the middle pipes
	if (input_fd)
		close(input_fd);
	// close the read input only in the last pipe
	if (cmd->next == NULL)
		close(fds[0]);
	input_fd = fds[0];
	return (input_fd);
}

void	pipes()
{
	int		fds[2];
	int		pid;
	int		intput_fd;
	t_command *tmp;

	tmp = g_shell.cmds;
	while (tmp)
	{
		pipe(fds);
		pid = fork();
		if (pid == 0)
			duper(tmp, fds, intput_fd);
		intput_fd = save_input_fd(tmp, fds, intput_fd);
		if (tmp->next == NULL || tmp->next->is_piped == 0)
			break;
		tmp = tmp->next;
	}
	while (wait(&pid) != -1)
		;
	// if (WIFEXITED(pid))
	// 	pid = (WEXITSTATUS(pid));
}
/*
index = 0
_ alpha
other indexs
_ alphanum
*/