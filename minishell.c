#include "minishell.h"

int remove_char(char *str,int index, int flag)
{
	int i;

	i = 0;
	if(!flag)
		flag = str[index];
	else
		flag = 0;
	while (str[index + i])
	{
		str[index + i] = str[index + i + 1];
		i++;
	}
	return (flag);
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

int get_args(char *cmd, t_command *new)
{
	int i;
	int j;
	int skip;

	j = 0;
	i = 0;
	
	//printf("%d\n",get_args_num(cmd));
	new->args = malloc((get_args_num(cmd) + 1) * sizeof(char *));
	while(cmd[i] == ' ')
		i++;
	while(cmd[i] && cmd[i] != '|')
	{
		skip = skip_arg(cmd, i);
		new->args[j] = malloc(skip - i + 1);
		ft_strlcpy(new->args[j], cmd + i, skip - i + 1);
		i = skip;
		while(cmd[i] == ' ')
			i++;
		j++;
	}
	new->args[j] = NULL;
	return i;
}

void skip_quote(t_command *cmd)
{
	int i = 0;
	int j;
	int flag;

	flag = 0;
	while(cmd->args[i])
	{
		j = 0;
		while(cmd->args[i][j])
		{
			if (!flag && (cmd->args[i][j] == 39 || cmd->args[i][j] == 34))
				flag = remove_char(cmd->args[i],j, flag);
			else if(cmd->args[i][j] == flag)				
				flag = remove_char(cmd->args[i], j, flag);
			else if (!flag && cmd->args[i][j] == '$')
				j = replace_env(&cmd->args[i], j);
			else
				j++;
		}
		i++;
	}
	if(flag)
		printf("Error: Multiline\n");
}

void get_cmds(char *cmd)
{
	int i;
	t_command *tmp;

	i = 0;
	tmp = g_shell.cmds;
	while(cmd[i])
	{
		i += get_args(cmd + i,tmp);
		skip_quote(tmp);
		if(cmd[i] == '|')
		{
			tmp->next = malloc(sizeof(t_command *));
			tmp = tmp->next;
			i++;
		}
		else
			tmp->next = NULL;	
	}
}

int main(int argc, char **argv, char **envp)
{

	char        *line;
	int i;
	char *s[] = {"echo", NULL};
	g_shell.env = malloc(sizeof(t_env *));
	g_shell.cmds = malloc(sizeof(t_command *));
	fill_env(envp);
	//print_env();
	while(1)
	{   
		line = readline("$>");
		get_cmds(line);
		//get_env_by_name(line);
		i = 0;
		g_shell.cmds = g_shell.cmds->next;
		while(g_shell.cmds->args[i])
		{
			printf("%ld|%s\n",ft_strlen(g_shell.cmds->args[i]) , g_shell.cmds->args[i]);
			i++;
		}
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