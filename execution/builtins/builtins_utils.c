/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:05:38 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/10 16:08:17 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	int	lenght;

	if (cmd)
	{
		lenght = ft_strlen(cmd) + 7;
		if (!ft_strncmp(cmd, "echo", lenght)
			|| !ft_strncmp(cmd, "cd", lenght)
			|| !ft_strncmp(cmd, "pwd", lenght)
			|| !ft_strncmp(cmd, "export", lenght)
			|| !ft_strncmp(cmd, "unset", lenght)
			|| !ft_strncmp(cmd, "env", lenght)
			|| !ft_strncmp(cmd, "exit", lenght))
			return (1);
		return (0);
	}
	return (2);
}

int	find_key(t_env *env, char *target)
{
	t_env	*tmp;

	if (env)
	{
		tmp = env;
		while (tmp)
		{
			if (!ft_strncmp(tmp->name, target, ft_strlen(tmp->name)
					+ ft_strlen(target)))
				return (1);
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}
	}
	return (0);
}

void	change_key_value(t_env *env, char *key_target, char *new_value)
{
	t_env	*tmp;

	if (new_value)
	{
		tmp = env;
		while (tmp)
		{
			if (!ft_strncmp(tmp->name, key_target, ft_strlen(tmp->name)
					+ ft_strlen(key_target)))
			{
				free(tmp->value);
				tmp->value = ft_strdup(new_value);
				free(new_value);
				return ;
			}
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}
		free(new_value);
	}
}

char	*get_key_value(t_env *env, char *key_target)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, key_target, ft_strlen(tmp->name)
				+ ft_strlen(key_target)))
			return (ft_strdup(tmp->value));
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_key_value(t_env *env, char *key, char *value)
{
	if (!find_key(env, key))
		add_node(&env, init_node(key, value));
	else
	{
		change_key_value(env, key, value);
		free(key);
	}
}
