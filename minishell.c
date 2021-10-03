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


int get_cmds(char **cmd)
{
	int i;
	t_command *tmp;

	i = 0;
	tmp = g_shell.cmds;
	g_shell.cmds->redirection = NULL;
	while((*cmd)[i])
	{
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

int main(int argc, char **argv, char **envp)
{

	char        *line;
	int i;
	char *s[] = {"echo", NULL};
	g_shell.env = malloc(sizeof(t_env));
	g_shell.cmds = malloc(sizeof(t_command));
	fill_env(envp);
	//print_env();
	while(1)
	{   
		line = readline("$>");
		add_history(line);
		if(get_cmds(&line) == -1)
			continue;

	// 	//get_redirection(&line, g_shell.cmds->redirection, 0);
	// 	printf("%s\n",g_shell.cmds->redirection->file);
	// 	//get_env_by_name(line);
	 	//i = 0;
		print_commands();
		// while(g_shell.cmds)
		// {
		// 	i = 0;
		// 	// while(g_shell.cmds->args[i])
		// 	// {
		// 	// 	printf("%s\n",g_shell.cmds->args[i]);
		// 	// 	i++;
		// 	// }
		// 	print_redirection(g_shell.cmds->redirection);
		// }
		free(line);
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