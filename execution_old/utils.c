#include "execution.h"

int     is_builtin(char *cmd)
{
	if (cmd)
	{
		if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)) || !ft_strncmp(cmd, "cd", ft_strlen(cmd)) ||
			!ft_strncmp(cmd, "pwd", ft_strlen(cmd)) || !ft_strncmp(cmd, "export", ft_strlen(cmd)) ||
			!ft_strncmp(cmd, "unset", ft_strlen(cmd)) || !ft_strncmp(cmd, "env", ft_strlen(cmd)) ||
			!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
			return (1);
		return(0);
	}
    return (2);
}

int exec_builtin(char **cmd)
{
	int		ret;

	if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
		ret = exec_echo(cmd);
	else if (!ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])))
		ret = exec_pwd();
	else if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
		ret = exec_cd(cmd);
	else if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
		ret = exec_export(cmd);
	else if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
		ret = exec_unset(cmd);
	else if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
		ret = exec_env(cmd);
	else if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
		exec_exit(cmd);
	return (ret);
}

char    *get_path()
{
    t_env   *tmp;

    if (g_shell.env)
    {
        tmp = g_shell.env;
        while (tmp)
        {
            if (!strcmp(tmp->name, "PATH"))
                return (ft_strdup(tmp->value));
			if (tmp->next == NULL)
				break;
            tmp = tmp->next;
        }
    }
	return (NULL);
}

int arr_lenght(char **arr)
{
    int     i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
}

int	find_key(t_env *env, char *target)
{
    t_env   *tmp;

    if (env)
    {
        tmp = env;
        while (tmp)
        {
            if (!strcmp(tmp->name, target))
                return (1);
			if (tmp->next == NULL)
				break;
            tmp = tmp->next;
        }
    }
	return (0);
}

void	change_key_value(t_env *env, char *key_target, char *new_value)
{
	t_env	*tmp;

	if (new_value)
	{
		tmp = env;
		while (tmp)
		{
			if (!strcmp(tmp->name, key_target))
			{
				free(tmp->value);
				tmp->value = ft_strdup(new_value);
    	        free(new_value);
			}
			if (tmp->next == NULL)
				break;
			tmp = tmp->next;
		}
	}
}

char	*get_key_value(t_env *env, char *key_target)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!strcmp(tmp->name, key_target))
			return (ft_strdup(tmp->value));
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_key_value(t_env *env, char *key, char *value)
{
	if (!find_key(env, key))
		add_node(&env, init_node(key, value));
	else
	{
		change_key_value(env, key, value);
		free(key);
	}
}

int	get_exitvalue(int ret)
{
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	else if (WIFSIGNALED(ret))
		return (128 + WTERMSIG(ret));
	return (ret);
}