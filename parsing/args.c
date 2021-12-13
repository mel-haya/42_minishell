/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:39:06 by mourad            #+#    #+#             */
/*   Updated: 2021/12/10 16:04:35 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_arg(char *cmd, int i)
{
	char	flag;

	flag = 0;
	while (cmd[i])
	{
		if (!flag && is_token(cmd[i]))
			return (i);
		if (!flag && (cmd[i] == 34 || cmd[i] == 39))
			flag = cmd[i];
		else if (flag == cmd[i])
			flag = 0;
		i++;
	}
	return (i);
}

int	get_args_num(char *cmd)
{
	int	i;
	int	args;

	args = 0;
	i = 0;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i])
	{
		i = skip_arg(cmd, i);
		args++;
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] == '|')
			return (args);
	}
	return (args);
}

int	get_args(char *cmd, t_command *new)
{
	int	i;
	int	j;
	int	skip;

	j = 0;
	i = 0;
	new->args = malloc((get_args_num(cmd) + 1) * sizeof(char *));
	if (!(new->args))
		exit_malloc_fail();
	while (cmd[i] == ' ')
		i++;
	while (cmd[i] && cmd[i] != '|')
	{
		skip = skip_arg(cmd, i);
		new->args[j] = malloc(skip - i + 1);
		if (!(new->args[j]))
			exit_malloc_fail();
		ft_strlcpy(new->args[j], cmd + i, skip - i + 1);
		i = skip;
		while (cmd[i] == ' ')
			i++;
		j++;
	}
	new->args[j] = NULL;
	return (i);
}

int	remove_quotes(char **s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while ((*s)[i])
	{
		if (!flag && ((*s)[i] == 39 || (*s)[i] == 34))
			flag = remove_char((*s), i, flag);
		else if ((*s)[i] == flag)
			flag = remove_char((*s), i, flag);
		else
			i++;
	}
	return (flag);
}

int	quote_args(t_command *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd->args[i])
	{
		flag = remove_quotes(&(cmd->args[i]));
		cmd->args[i] = tokenize_line(cmd->args[i]);
		i++;
	}
	if (flag)
	{
		printf("minishell: Unclosed quotes\n");
		g_shell.status = 1;
		return (flag);
	}
	return (0);
}
