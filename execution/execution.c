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

// void	print_lst(t_env *lst)
// {
// 	t_env *tmp;

// 	tmp = lst;
// 	if (lst)
// 	{
// 		while (lst->next != NULL)
// 		{
// 			// if (ft_strncmp(lst->key, "OLDPWD", 6) == 0 || ft_strncmp(lst->key, "PWD", 3) == 0)
// 				// printf("key:| %s | value:| %s |\n", lst->key, lst->value);
// 				printf("%s%s\n", lst->key, lst->value);
// 			lst = lst->next;
// 		}
// 		// if (ft_strncmp(lst->key, "OLDPWD", 6) == 0 || ft_strncmp(lst->key, "PWD", 3) == 0)
// 			// printf("key:| %s | value:| %s |\n", lst->key, lst->value);
// 				printf("%s%s\n", lst->key, lst->value);
// 	}
// }

// void	init_env(t_env **env_lst, char **env)
// {
// 	int		i;
// 	char	**splited_env;
// 	char	*key;
// 	char	*value;

// 	i = 0;
// 	while (env[i])
// 	{
// 		splited_env = ft_split(env[i++], '=');
// 		key = ft_strdup(splited_env[0]);
// 		value = ft_strjoin("=", splited_env[1]);
// 		add_node(env_lst, init_node(key, value));
// 		free_arr(splited_env);
// 	}
// }

void	exec(char *bin, char **cmd, char *err_output)
{
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
		return (cmd);
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
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		exec(bin, cmd, err_output);
	if (path)
		free(bin);
	waitpid(pid, 0, 0);
	// ADD cHILD PROCESS TERMINATION STATUS CHECK
}

void	command_exec(t_env *env, t_command *cmd)
{
	char	*path;
	char	*err_msg;

	err_msg = path_case_error(env);
	path = get_path();
	if (!is_builtin(cmd->args[0]))
		exec_cmd(path, cmd->args, err_msg);
	else
		exec_builtin(cmd->args);
	free(err_msg);
}

void	exec_redir(t_redirection *redir)
{
	t_redirection *tmp;
	int		file;

	tmp = redir;

	while (tmp)
	{
		if (tmp->token == '>')
		{
			file = open(redir->file, O_WRONLY | O_TRUNC);
			dup2(file, 1);
			close(file);
		}
		else if (tmp->token == '>' && tmp->append)
		{
			file = open(redir->file, O_WRONLY | O_APPEND, 0644);
			dup2(file, 1);
			close (file);
		}
		else if (tmp->token == '<')
		{
			file = open(redir->file, O_RDONLY);
			dup2(file, 0);
			close(file);
			// if (!ft_strncmp(redir->file, "/tmp/", 5))
			// 	unlink(redir->file);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}

void	builtin_redir()
{
	int		pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		exec_redir(g_shell.cmds->redirection);
		exec_builtin(g_shell.cmds->args);
		exit(0);
	}
	waitpid(pid, 0, 0);
	// ADD SHILD PROCESS TERMINATION STATUS CHECK
}

void	cmd_redir(char *err_msg)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		exec_redir(g_shell.cmds->redirection);
		exec_cmd(get_path(), g_shell.cmds->args, err_msg);
		exit(0);
	}
	waitpid(pid, 0, 0);
	// ADD SHILD PROCESS TERMINATION STATUS CHECK
}

char	*path_case_error()
{
	char *path;

	path = get_path(g_shell.env);
	if (path)
	{
		free(path);
		return (ft_strdup("command not found"));
	}
	else
		return (ft_strdup("No such file or directory"));
}

void	redir_exec()
{
	char *err_msg;

	err_msg = path_case_error();
	filter_redir(g_shell.cmds->redirection);
	if (is_builtin(g_shell.cmds->args[0]))
		builtin_redir();
	else if (is_builtin(g_shell.cmds->args[0]) == 0)
		cmd_redir(err_msg);
	else if (is_builtin(g_shell.cmds->args[0]) == 2)
		exec_redir(g_shell.cmds->redirection);
	free(err_msg);
}

void	execution()
{
	if (g_shell.cmds->redirection == NULL) // if there is no pipes and no redirections
		command_exec(g_shell.env, g_shell.cmds);
	if (g_shell.cmds->redirection) // if there is no pipes
		redir_exec();
}

