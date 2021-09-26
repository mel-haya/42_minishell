#include "minishell.h"

t_env	*get_env_by_name(char *name)
{
	t_env *tmp;
	int len;

	tmp = g_shell.env;
	len = 0;
	while(name[len] && (name[len] != 34 && name[len] != 39))
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
	printf("%s\n",tmp->value);
	return NULL;
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

	tmp = g_shell.env;
	i = 0;
	while(envp[i])
	{
		name_size = env_name_len(envp[i]);
		tmp->name = malloc(name_size + 3);
		tmp->value = malloc(ft_strlen(envp[i]) - name_size + 1);
		ft_strlcpy(tmp->name, envp[i], name_size + 1);
		ft_strlcpy(tmp->value, envp[i] + name_size + 1, ft_strlen(envp[i]) - name_size + 1);
		if(envp[i + 1])
		{
			tmp->next = malloc(sizeof(t_env *));
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

int replace_env(char **arg, int index)
{
	char	*after;
	int		len;
	char	*value;
	t_env	*env;
	char	*new;

	env = get_env_by_name((*arg) + index + 1);
	if (!env)
		value = "";
	else	
		value = env->value;
	after = (*arg) + index + ft_strlen(env->name) + 1;
	len = index + ft_strlen(value) + ft_strlen(after) + 2;
	new = malloc(len);
	ft_strlcpy(new, *arg, index + 1);
	ft_strlcpy(new + index, value, ft_strlen(value) + 1);
	ft_strlcpy(new + index + ft_strlen(value), after, ft_strlen(after) + 1);
	free(*arg);
	*arg = new;
	return index + ft_strlen(env->value);
}
