#include "minishell.h"

int get_cmds(char **cmd)
{
	int i;
	t_command *tmp;

	i = 0;
	tmp = g_shell.cmds;	
	while((*cmd)[i])
	{
		tmp->redirection = NULL;
		if (get_redirections(cmd, tmp, i) == -1)
			return -1;
		//printf("%s\n", *cmd);
		i += get_args(*cmd + i,tmp);
		quote_args(tmp);
		if((*cmd)[i] == '|')
		{
			tmp->next = malloc(sizeof(t_command));
			tmp = tmp->next;
			i++;
		}
		else
			tmp->next = NULL;	
	}
}

void free_cmds()
{
	t_command *tmp;
	t_redirection *red;
	int i;
 
	while(g_shell.cmds)
	{
		i = 0;
		while((g_shell.cmds->args)[i])
		{
			free((g_shell.cmds->args)[i]);
			i++;
		}
		free(g_shell.cmds->args);
		while(g_shell.cmds->redirection)
		{
			red = g_shell.cmds->redirection->next;
			free(g_shell.cmds->redirection->file);
			free(g_shell.cmds->redirection);
			g_shell.cmds->redirection = red;
		}
		tmp = g_shell.cmds->next;
		free(g_shell.cmds);
		g_shell.cmds = tmp;
	}
}

void print_redirection(t_redirection *r)
{

	while(r)
	{
		if(r->append)
			printf("%c",r->token);
		printf("%c%s ",r->token, r->file);
		r = r->next;
	}
}
void print_commands()
{
	t_command *tmp = g_shell.cmds;
	int i;

	while(tmp)
	{
		i = 0;
		while(tmp->args[i])
		{
			printf("%s ", tmp->args[i]);
			i++;
		}
		if(tmp->redirection)
			print_redirection(tmp->redirection);
		tmp = tmp->next;
		printf(" | ");
	}
	printf("\n");
}

int init_global()
{
	g_shell.env = malloc(sizeof(t_env));
	if (!g_shell.env || !g_shell.cmds)
		return (1);
	g_shell.status = 0;
	g_shell.heredocn = 0;
	return (0);
}

int main(int argc, char **argv, char **envp)
{

	char        *line;
	int i;
	char *s[] = {"echo", NULL};

	init_global();
	fill_env(envp);
	//print_env();
	while(1)
	{   
		line = readline("$>");
		g_shell.cmds = malloc(sizeof(t_command));
		add_history(line);
		if(get_cmds(&line) == -1)
			continue;
		print_commands();
		free(line);
		free_cmds();
		int id ;//= fork();
		if(id != 0)
			wait(NULL);
		else
		{
			return 0;
		}
	}
	return 0;
}