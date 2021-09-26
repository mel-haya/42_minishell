#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


typedef struct s_command
{
	char **args;
	int i;
	struct s_command *next;
}               t_command;

typedef struct s_env
{
	char    *name;
	char    *value;
	struct s_env   *next;
}               t_env;

typedef struct  s_global
{
	t_command   *cmds;
	t_env       *env;
	int         status;
}               t_global;

t_global g_shell;

t_env	*get_env_by_name(char *name)
{
	t_env *tmp;
	int len;

	tmp = g_shell.env;
	len = 0;
	while(name[len] && (name[len] != 34 || name[len] == 39))
		len++;
	while(tmp)
	{
		if(!ft_strncmp(name, tmp->name,len))
		{
			//printf("%s\n",tmp->value);
			return tmp;
		}
		tmp = tmp->next;
	}
	printf("%s\n",tmp->value);
	return NULL;
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
	ft_strlcpy(new + index + ft_strlen(value), after, ft_strlen(after));
	free(*arg);
	*arg = new;
	return index + ft_strlen(env->value) - 2;
}



void remove_char(char *str,int index)
{
	int i;

	i = 0;
	while (str[index + i])
	{
		str[index + i] = str[index + i + 1];
		i++;
	}

}

int skip_arg(char *cmd, int i)
{
	char flag;

	flag = 0;
	while (cmd[i])
	{
		if (!flag && (cmd[i] == ' ' || cmd[i] == '|'))
		{
			return i;
		}
		if (!flag && (cmd[i] == 34 || cmd[i] == 39))
		{
			flag = cmd[i];
			i++;
		}
		else if (flag == cmd[i + 1])
			flag = 0;
		i++;
	}
	return i;
}

int get_args_num(char *cmd)
{
	int i;
	int args;

	args = 0;
	i = 0;
	while(cmd[i] == ' ')
		i++;
	while(cmd[i])
	{
		i = skip_arg(cmd, i);
		args++;
		while(cmd[i] == ' ')
			i++;
		if(cmd[i] == '|')
			return args;     
	}
	return args;
}

void get_args(char *cmd)
{
	int i;
	int j;
	int skip;

	j = 0;
	i = 0;
	
	printf("%d\n",get_args_num(cmd));
	g_shell.cmds->args = malloc((get_args_num(cmd) + 1) * sizeof(char *));
	while(cmd[i] == ' ')
		i++;
	while(cmd[i])
	{
		skip = skip_arg(cmd, i);
		g_shell.cmds->args[j] = malloc(skip - i + 1);
		ft_strlcpy(g_shell.cmds->args[j], cmd + i, skip - i + 1);
		i = skip;
		while(cmd[i] == ' ')
			i++;
		j++;
	}
	g_shell.cmds->args[get_args_num(cmd)] = NULL;
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

void skip_quote()
{
	int i = 0;
	int j;
	int flag;

	flag = 0;
	while(g_shell.cmds->args[i])
	{
		j = 0;
		while(g_shell.cmds->args[i][j])
		{
			if (!flag && (g_shell.cmds->args[i][j] == 39 || g_shell.cmds->args[i][j] == 34))
			{
				flag = g_shell.cmds->args[i][j];
				remove_char(g_shell.cmds->args[i],j);
			}
			else if(g_shell.cmds->args[i][j] == flag)
			{
				flag = 0;
				remove_char(g_shell.cmds->args[i],j);
			}
			else if (!flag && g_shell.cmds->args[i][j] == '$')
				j += replace_env(&g_shell.cmds->args[i], j);
			j++;
		}
		if(flag)
			printf("Error: Multiline\n");
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{

	char        *line;

	char *s[] = {"echo", NULL};
	g_shell.env = malloc(sizeof(t_env *));
	g_shell.cmds = malloc(sizeof(t_command *));
	fill_env(envp);
	//print_env();
	while(1)
	{   
		line = readline("$>");
		get_args(line);
		//get_env_by_name(line);
		skip_quote();
		printf("%s\n", g_shell.cmds->args[0]);
		int id ;//= fork();
		if(id != 0)
			wait(NULL);
		else
		{
			//execve(line,s,envp);
			return 0;
		}
	}
	return 0;
}