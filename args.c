/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourad <mourad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:39:06 by mourad            #+#    #+#             */
/*   Updated: 2021/11/08 18:30:58 by mourad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (flag == cmd[i + 1])
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
	while (cmd[i] == ' ')
		i++;
	while (cmd[i] && cmd[i] != '|')
	{
		skip = skip_arg(cmd, i);
		new->args[j] = malloc(skip - i + 1);
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
		else if (flag != 39 && (*s)[i] == '$' && \
		(*s)[i + 1] && (*s)[i + 1] != '$')
			i = expand_env(s, i);
		else
			i++;
	}
	return (flag);
}

void	quote_args(t_command *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd->args[i])
	{
		flag = remove_quotes(&(cmd->args[i]));
		i++;
	}
	if (flag)
		printf("Error: Multiline\n");
}
