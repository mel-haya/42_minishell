#include "minishell.h"


int is_token(char c)
{
	if(c == ' ' || c == '|' || c == '<'|| c == '>')
		return (1);
	else
		return (0);
}

int skip_arg(char *cmd, int i)
{
	char flag;

	flag = 0;
	while (cmd[i])
	{
		if (!flag && is_token(cmd[i]))
			return i;
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

int remove_quotes(char **s)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while((*s)[i])
	{
		if (!flag && ((*s)[i] == 39 || (*s)[i] == 34))
			flag = remove_char((*s), i, flag);
		else if((*s)[i] == flag)				
			flag = remove_char((*s), i, flag);
		else if (flag != 39 && (*s)[i] == '$')
			i = expand_env(s, i);
			else
		i++;
	}
	return flag;
}


void quote_args(t_command *cmd)
{
	int i = 0;
	int flag;

	flag = 0;
	while(cmd->args[i])
	{
		flag = remove_quotes(&(cmd->args[i]));
		i++;
	}
	if(flag)
		printf("Error: Multiline\n");
}

int get_redirections(char **str, t_command *cmd, int i)
{
	t_redirection *tmp;

	int flag = 0;
	
	while((*str)[i] && (*str)[i] != '|')
	{
		while((*str)[i] == ' ')
		i++;
		if((*str)[i] == '<' || (*str)[i] == '>')
		{
			if(!cmd->redirection)
			{
				cmd->redirection = malloc(sizeof(t_redirection));
				tmp = cmd->redirection;
			}
			else{
				tmp->next = malloc(sizeof(t_redirection));
				tmp = tmp->next;	
			}
			if((get_redirection(str, tmp, i)) == -1)
			{
				tmp->next = NULL;
				return (-1);
			}
			flag++;
		}
		else
			i = skip_arg(*str, i);
	}
	if(flag)
		tmp->next = NULL;
	return 0;
}

int get_redirection(char **str, t_redirection *r, int i)
{
	int j;
	int len;

	j = i + 1;
	r->token = (*str)[i];
	if((*str)[j] == (*str)[i])
		r->append = 1;
	else
		r->append = 0;
	j += r->append;
	while ((*str)[j] == ' ')
		j++;
	if(is_token((*str)[j]))
	{
		printf("syntax error near unexpected token '%c'\n", (*str)[j]);
		return (-1);
	}
	len = skip_arg(*str, j);
	r->file = malloc(len - j + 1);
	ft_strlcpy(r->file, (*str) + j, len - j + 1);
	if (r->token == '<' && r->append)
		r->file = here_doc(r->file);
	remove_quotes(&(r->file));
	remove_str(str, i, len - i);
	return 0;
}