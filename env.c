#include "minishell.h"

t_env	*get_env_by_name(char *name)
{
	t_env *tmp;
	int len;

	tmp = g_shell.env;
	len = 0;
	while(name[len] && (name[len] != 34 && name[len] != 39 && name[len] != ' ' && name[len] != '$'))
		len++;
	while(tmp)
	{
		if(!ft_strncmp(name, tmp->name,len) && ft_strlen(tmp->name) == len)
		{
			//printf("%s\n",tmp->value);
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

int new_env(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if(!new)
		return (-1);
	new->name = name;
	new->value = value;
	new->next = g_shell.env;
	g_shell.env = new;
	return (0);
}

int env_name_len(char *env)
{
	int i;

	i = 0;
	while(env[i] != '=')
		i++;
	return (i);
}

void fill_env(char **envp)
{
	int i;
	t_env *tmp;
	int name_size;
	int test;

	tmp = g_shell.env;
	i = 0;
	while(envp[i])
	{
		name_size = env_name_len(envp[i]);
		tmp->name = malloc(name_size + 1);
		test = (ft_strlen(envp[i]) - name_size);
		tmp->value = malloc(test);
		ft_strlcpy(tmp->name, envp[i], name_size + 1);
		ft_strlcpy(tmp->value, envp[i] + name_size + 1, ft_strlen(envp[i]) - name_size + 1);
		if(envp[i + 1])
		{
			tmp->next = malloc(sizeof(t_env));
			tmp = tmp->next;
		}
		else
			tmp->next = NULL;
		i++;
	}
}

void print_env()
{
	t_env *env = g_shell.env;
	while(env)
	{
		
		printf("%s=%s\n",env->name, env->value);
		env = env->next;
	} 
}

int expand_status(char **arg, int index)
{
	char	*value;
	char	*new;
	int ret;


	value = ft_itoa(g_shell.status);
	ret = index + ft_strlen(value);
	new = malloc(ft_strlen(*arg) + ft_strlen(value) - 1);
	ft_strlcpy(new, *arg, index + 1);
	ft_strlcpy(new + index, value, ft_strlen(value) + 1);
	ft_strlcpy(new + index + ft_strlen(value), (*arg) + index + 2 , ft_strlen((*arg) + index + 2) + 1);
	free(*arg);
	free(value);
	*arg = new;
	return ret;
}

int expand_env(char **arg, int index)
{
	char	*after;
	int		len;
	char	*value;
	t_env	*env;
	char	*new;

	if((*arg)[index + 1] == '?')
		return (expand_status(arg, index));
	env = get_env_by_name((*arg) + index + 1);
	after = (*arg) + index + 1;
	if (!env)
		value = "";
	else
		value = env->value;
	while(*after && (*after != 34 && *after != 39 && *after != ' ' && *after != '$'))
		after++;
	len = index + ft_strlen(value) + ft_strlen(after) + 2;
	new = malloc(len);
	ft_strlcpy(new, *arg, index + 1);
	ft_strlcpy(new + index, value, ft_strlen(value) + 1);
	ft_strlcpy(new + index + ft_strlen(value), after, ft_strlen(after) + 1);
	free(*arg);
	*arg = new;
	return index + ft_strlen(value);
}
