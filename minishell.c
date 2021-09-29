#include "minishell.h"

// int validate_token(char *line)
// {
// 	int i;

// 	i = 0;

// }

// int	get_redirections(char *line, t_command *cmd)
// {
// 	int i;

// 	i = 0;
// 	cmd->redirection = malloc(sizeof(t_redirection *));
// 	cmd->redirection->token = *line;
// 	if(line[1] == line[0])
// 		cmd->redirection->token = 1;
// 	else if(line[0] == line[0] )
// 	else
// 		cmd->redirection->token = 0;

// 	while(line[i])
// }


void get_cmds(char *cmd)
{
	int i;
	t_command *tmp;

	i = 0;
	tmp = g_shell.cmds;
	while(cmd[i])
	{
		i += get_args(cmd + i,tmp);
		quote_args(tmp);
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
		while(!i)
		{
			
			while(g_shell.cmds->args[i])
			{
				remove_str(&g_shell.cmds->args[0], 1, 2);
				printf("%s\n",g_shell.cmds->args[0]);
				i++;
			}
			//printf("*");
			//g_shell.cmds = g_shell.cmds->next;
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