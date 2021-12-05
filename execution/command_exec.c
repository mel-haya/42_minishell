/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:55:22 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/05 04:38:40 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	if (!bin_path)
		return (0);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		free_arr(bin_path);
		return (ft_strdup(cmd));
	}
	while (bin_path[++i])
	{
		cmd_path = build_cmdpath(bin_path[i], cmd);
		ret = access(cmd_path, F_OK);
		if (ret == 0)
			break ;
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
	if (pid == 0)
		exec(bin, cmd, err_output);
	if (path)
		free(bin);
	wait(&pid);
	g_shell.status = get_exitvalue(pid);
}

int	command_exec(t_command *cmd)
{
	char	*path;
	char	*err_msg;
	int		ret;

	err_msg = path_case_error();
	path = get_path();
	g_shell.is_forked = 1 + cmd->is_piped;
	signal(SIGQUIT, global_sig_handler);
	if (!is_builtin(cmd->args[0]))
		exec_cmd(path, cmd->args, err_msg);
	else
		g_shell.status = exec_builtin(cmd->args);
	free(err_msg);
	free(path);
	return (ret);
}
