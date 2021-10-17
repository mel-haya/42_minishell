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

void	exec_cmd(char *bin, char **cmd)
{
	if (execve(bin, cmd, NULL) == -1)
	{
		exit_err(cmd[0], 127, 2);
	}
	else
		exit(126);
}

void	exec(t_env *env, t_command *cmd)
{
	int		pid;
	char	*bin;
	char	*path;
	char	**bin_path;

	path = get_path(env);
	if (path)
	{
		if (!is_builtin(cmd->args[0]))
		{
			bin_path = ft_split(path, ':');
			bin = get_bin(bin_path, cmd->args[0]);
			g_shell.is_forked = 1;
			pid = fork();
			if (pid)
				wait(NULL);
			else
				exec_cmd(bin, cmd->args);
			g_shell.is_forked = 0;
			free(bin);
		}
		else
			exec_builtin(cmd->args);
		free(path);
	}
}

void	execution()
{
	// t_env	*env_lst;

	exec(g_shell.env, g_shell.cmds);
	// (void)argc;
    // (void)argv;
	// env_lst = NULL;
	// init_env(&env_lst, env);

	// char *cmd2[] = {"export", "mouad=", "mouad1=", "mouad2=", "mouad3=", NULL};
	// char *cmd3[] = {"exit", NULL};
	// char *cmd1[] = {"exit", "1", NULL};
	// char *cmd2[] = {"echo", "test", "1", "2", NULL};

	// printf("-----------BEFOR--------\n");
	// print_lst(env_lst);
	// exec(env_lst, cmd2);
	// exec(env_lst, cmd3);
	// exec(env_lst, cmd1);

	// printf("-----------AFTER--------\n");
	// print_lst(env_lst);

	// printf("--------------------------------\n");

	// exec(env_lst, cmd2);
	// printf("-----------AFTER--------\n");
	// print_lst(env_lst);

	// free_lst(&env_lst);
	// system("leaks minishell");
	// return (0);
}

// int		main(int argc, char **argv, char **env)
// {
// 	test(env);
// 	// system("leaks minishell"); 	q
// 	(void)argc;
// 	(void)argv;
// 	return (0);
// }
