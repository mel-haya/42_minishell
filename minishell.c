/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:31:26 by mourad            #+#    #+#             */
/*   Updated: 2021/12/05 21:04:03 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd(char **cmd, t_command *tmp, int i)
{
	tmp->redirection = NULL;
	tmp->args = NULL;
	tmp->next = NULL;
	tmp->red_in = NULL;
	tmp->red_out = NULL;
	return (get_redirections(cmd, tmp, i));
}

int	check_next_cmd(char *str, int i)
{
	i++;
	while (str[i] == ' ')
		i++;
	if (!str[i])
	{
		printf("minishell : syntax error near unexpected token '|'\n");
		g_shell.status = 1;
		return (-1);
	}
	return (i);
}

int	get_cmds(char **cmd)
{
	int			i;
	t_command	*tmp;

	i = 0;
	tmp = g_shell.cmds;
	while ((*cmd)[i])
	{
		if (init_cmd(cmd, tmp, i) == -1)
			return (-1);
		i += get_args(*cmd + i, tmp);
		if (quote_args(tmp))
			return (-1);
		if ((*cmd)[i] == '|')
		{
			i = check_next_cmd(*cmd, i);
			if (i == -1)
				return (i);
			tmp->next = malloc(sizeof(t_command));
			tmp->next->is_piped = 1;
			tmp = tmp->next;
		}
	}
	return (0);
}

// void	print_redirection(t_redirection *r)
// {
// 	while (r)
// 	{
// 		if (r->append)
// 			printf("%c", r->token);
// 		printf("%c%s ", r->token, r->file);
// 		r = r->next;
// 	}
// }
// void	print_commands()
// {
// 	t_command *tmp = g_shell.cmds;
// 	int i;

// 	while(tmp)
// 	{
// 		i = 0;
// 		while(tmp->args[i])
// 		{
// 			printf("%s ", tmp->args[i]);
// 			i++;
// 		}
// 		if(tmp->redirection)
// 			print_redirection(tmp->redirection);
// 		tmp = tmp->next;
// 		printf(" | ");
// 	}
// 	printf("\n");
// }

int	check_line(char **line)
{
	if (!*line)
	{
		printf("exit\n");
		exit(0);
	}
	if (*line[0])
		add_history(*line);
	expand_line(line);
	if (is_empty_line(*line))
	{
		free(*line);
		return (1);
	}
	g_shell.cmds = malloc(sizeof(t_command));
	g_shell.cmds->is_piped = 0;
	if (get_cmds(line) == -1)
	{
		free(*line);
		free_cmds();
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	init_global();
	ignctl();
	fill_env(envp);
	while (1)
	{
		set_global_signals();
		g_shell.is_forked = 0;
		g_shell.heredocn = 0;
		if (g_shell.status)
			line = readline("\001\e[32m\033[31m\002minishell%\
\001\e[0m\033[0m\002 ");
		else
			line = readline("\001\e[32m\033[1m\002minishell%\
\001\e[0m\033[0m\002 ");
		if (check_line(&line))
			continue ;
		execution();
		free(line);
		free_cmds();
	}
	return (0);
}
