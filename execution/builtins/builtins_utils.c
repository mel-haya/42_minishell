/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:05:38 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 16:05:42 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_builtin(char *cmd)
{
	if (cmd)
	{
		if (!ft_strncmp(cmd, "echo", ft_strlen(cmd))
			|| !ft_strncmp(cmd, "cd", ft_strlen(cmd))
			|| !ft_strncmp(cmd, "pwd", ft_strlen(cmd))
			|| !ft_strncmp(cmd, "export", ft_strlen(cmd))
			|| !ft_strncmp(cmd, "unset", ft_strlen(cmd))
			|| !ft_strncmp(cmd, "env", ft_strlen(cmd))
			|| !ft_strncmp(cmd, "exit", ft_strlen(cmd)))
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
			if (!strcmp(tmp->name, target))
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
			if (!strcmp(tmp->name, key_target))
			{
				free(tmp->value);
				tmp->value = ft_strdup(new_value);
				free(new_value);
			}
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}
	}
}

char	*get_key_value(t_env *env, char *key_target)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!strcmp(tmp->name, key_target))
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
