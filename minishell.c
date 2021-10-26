/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourad <mourad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:31:26 by mourad            #+#    #+#             */
/*   Updated: 2021/10/26 16:30:22 by mourad           ###   ########.fr       */
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
		quote_args(tmp);
		if ((*cmd)[i] == '|')
		{
			if ((*cmd)[i] == 0)
			{
				printf("Error: Multiline\n");
				tmp->next = NULL;
				return (-1);
			}
			tmp->next = malloc(sizeof(t_command));
			tmp = tmp->next;
			i++;
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

int	init_global(void)
{
	g_shell.env = malloc(sizeof(t_env));
	g_shell.is_forked = 0;
	if (!g_shell.env || !g_shell.cmds)
		return (1);
	g_shell.status = 0;
	ignctl();
	return (0);
}

int	check_line(char **line)
{
	if (!*line)
	{
		printf("exit\n");
		exit(0);
	}
	if (!**line)
	{
		free(*line);
		return (1);
	}
	g_shell.cmds = malloc(sizeof(t_command));
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
		g_shell.heredocn = 0;
		line = readline("\001\e[32m\033[1m\002minishell%\
\001\e[0m\033[0m\002 ");
		add_history(line);
		if (check_line(&line))
			continue ;
		execution();
		free(line);
		free_cmds();
	}
	return (0);
}
