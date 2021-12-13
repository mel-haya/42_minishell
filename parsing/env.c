/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:20:30 by mourad            #+#    #+#             */
/*   Updated: 2021/12/10 16:04:45 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env_by_name(char *name)
{
	t_env	*tmp;
	int		len;

	tmp = g_shell.env;
	len = 0;
	while (name[len] && (ft_isalnum(name[len]) || name[len] == '_'))
		len++;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, len)
			&& (int)ft_strlen(tmp->name) == len)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	env_name_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

void	fill_env(char **envp)
{
	int		name_size;
	int		i;
	t_env	*tmp;

	tmp = g_shell.env;
	i = -1;
	while (envp[++i])
	{
		name_size = env_name_len(envp[i]);
		tmp->name = malloc(name_size + 1);
		if (!(tmp->name))
			exit_malloc_fail();
		tmp->value = get_value(envp[i], name_size);
		ft_strlcpy(tmp->name, envp[i], name_size + 1);
		if (envp[i + 1])
		{
			tmp->next = malloc(sizeof(t_env));
			tmp = tmp->next;
			if (!tmp)
				exit_malloc_fail();
		}
		else
			tmp->next = NULL;
	}
}

int	check_piped(char *str, int j)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while (i < j)
	{
		if (!flag && (str[i] == 39 || str[i] == 34))
			flag = str[i];
		else if ((flag == str[i]) && (str[i] == 39 || str[i] == 34))
			flag = 0;
		if (!flag && str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	expand_status(char **arg, int index)
{
	char	*value;
	char	*new;
	int		ret;

	if (check_piped(*arg, index))
		g_shell.status = 0;
	value = ft_itoa(g_shell.status);
	ret = index + ft_strlen(value);
	new = malloc(ft_strlen(*arg) + ft_strlen(value) - 1);
	if (!new)
		exit_malloc_fail();
	ft_strlcpy(new, *arg, index + 1);
	ft_strlcpy(new + index, value, ft_strlen(value) + 1);
	ft_strlcpy(new + index + ft_strlen(value), (*arg) + \
	index + 2, ft_strlen((*arg) + index + 2) + 1);
	free(*arg);
	free(value);
	*arg = new;
	return (ret);
}
