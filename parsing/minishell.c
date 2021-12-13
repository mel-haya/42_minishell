/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:31:26 by mourad            #+#    #+#             */
/*   Updated: 2021/12/11 23:54:43 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_cmd(char **cmd, t_command *tmp, int i)
{
	tmp->redirection = NULL;
	tmp->args = NULL;
	tmp->next = NULL;
	tmp->red_in = NULL;
	tmp->red_out = NULL;
	return (get_redirections(cmd, tmp, i));
}

int	check_next_cmd(char *str, int i, t_command	*tmp)
{
	i++;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		g_shell.status = 1;
		return (-1);
	}
	tmp->next = malloc(sizeof(t_command));
	if (!(tmp->next))
		exit_malloc_fail();
	tmp->next->is_piped = 1;
	return (i);
}

int	get_cmds(char **cmd)
{
	int			i;
	t_command	*tmp;
	int			arg_len;

	i = 0;
	tmp = g_shell.cmds;
	while ((*cmd)[i])
	{
		if (init_cmd(cmd, tmp, i) == -1)
			return (-1);
		arg_len = get_args(*cmd + i, tmp);
		i += arg_len;
		if (arg_len == -1 || quote_args(tmp))
			return (-1);
		if ((*cmd)[i] == '|')
		{
			i = check_next_cmd(*cmd, i, tmp);
			if (i == -1)
				return (i);
			tmp = tmp->next;
		}
	}
	return (0);
}

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
	if (!(g_shell.cmds))
		exit_malloc_fail();
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
	fill_env(envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		set_global_signals();
		g_shell.heredocn = 0;
		line = readline("\001\e[32m\033[1m\002minishell%\
\001\e[0m\033[0m\002 ");
		if (check_line(&line))
			continue ;
		execution();
		free(line);
		free_cmds();
	}
	free_env();
	return (0);
}
