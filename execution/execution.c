#include "execution.h"

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

void	exec(char *bin, char **cmd, char *err_output)
{
	g_shell.is_forked = 2;
	if (execve(bin, cmd, NULL) == -1)
	{
		exit_err(cmd[0], err_output, 2);
		exit(127);
	}
	else
		exit(126);
}

char	*build_cmdpath(char *path, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	tmp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (cmd_path);
}

char	*get_bin(char **bin_path, char *cmd)
{
	int		i;
	int		ret;
	char	*cmd_path;

	i = -1;
	if (cmd[0] == '/' || cmd[0] == '.' || !bin_path)
	{
		free_arr(bin_path);
		return (ft_strdup(cmd));
	}
	while (bin_path[++i])
	{
		cmd_path = build_cmdpath(bin_path[i], cmd);
		ret = access(cmd_path, F_OK);
		if (ret == 0)
			break;
		free(cmd_path);
	}
	if (ret != 0)
		cmd_path = NULL;
	free_arr(bin_path);
	return (cmd_path);
}


void	exec_cmd(char *path, char **cmd, char *err_output)
{
	int		pid;
	char	*bin;
	char	**bin_path;

	bin_path = ft_split(path, ':');
	bin = get_bin(bin_path, cmd[0]);
	g_shell.is_forked = 1;
	signal(SIGQUIT, global_sig_handler);
	pid = fork();
	if (pid == 0)
		exec(bin, cmd, err_output);
	if (path)
		free(bin);
	wait(&pid);
	g_shell.is_forked = 0;
	signal(SIGQUIT, SIG_IGN);
	g_shell.status = get_exitvalue(pid);
}

int command_exec(t_env *env, t_command *cmd)
{
	char	*path;
	char	*err_msg;
	int		ret;

	err_msg = path_case_error(env);
	path = get_path();

	if (!is_builtin(cmd->args[0]))
		exec_cmd(path, cmd->args, err_msg);
	else
		g_shell.status = exec_builtin(cmd->args);
	free(err_msg);
	free(path);
	return (ret);
}

int open_f(char *f, t_redirection *tmp)
{
	int file;

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
	t_redirection *tmp;
	int		file;

	tmp = redir;

		// printf("code was here \n");
	while (tmp)
	{
		file = open_f(redir->file, tmp);
		if (tmp->token == '>' && !tmp->append)
		{
			dup2(file, 1);
		}
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

void	builtin_redir(t_command *cmd)
{
	exec_redir(cmd->redirection);
	exec_builtin(cmd->args);
}

void	cmd_redir(char *err_msg, t_command *cmd)
{
	exec_redir(cmd->redirection);
	exec_cmd(get_path(), cmd->args, err_msg);
}

int	is_path_exist(t_env *env)
{
	t_env   *tmp;

    if (env)
    {
        tmp = env;
        while (tmp)
        {
            if (!strcmp(tmp->name, "PATH"))
                return (1);
			if (tmp->next == NULL)
				break;
            tmp = tmp->next;
        }
    }
	return (0);
}

char	*path_case_error()
{
	if (is_path_exist(g_shell.env))
		return (ft_strdup("command not found"));
	else
		return (ft_strdup("No such file or directory"));
}

void	fds_saver(int *fds, int lock)
{
	if (lock == 0)
	{
		fds[0] = dup(0);
		fds[1] = dup(1);
	}
	else
	{
		dup2(fds[0], 0);
		dup2(fds[1], 1);
	}
}

void	redir_exec(t_command *cmd)
{
	char *err_msg;
	int		fds[2];

	if (filter_redir(cmd->redirection))
	{
		err_msg = path_case_error();
		fds_saver(fds, 0);
		if (is_builtin(cmd->args[0]))
			builtin_redir(cmd);
		else if (is_builtin(cmd->args[0]) == 0)
			cmd_redir(err_msg, cmd);
		else if (is_builtin(cmd->args[0]) == 2)
			exec_redir(cmd->redirection);
		fds_saver(fds, 1);
		free(err_msg);
	}
}

void	execution()
{
	// foo = fopen("/tmp/loggs", "a");
	if (!g_shell.cmds->next && !g_shell.cmds->redirection)
		command_exec(g_shell.env, g_shell.cmds);
	else if (!g_shell.cmds->next && g_shell.cmds->redirection)
		redir_exec(g_shell.cmds);
	else if (g_shell.cmds->next)
		pipes();
	// printf("status = %d\n", g_shell.status);
}