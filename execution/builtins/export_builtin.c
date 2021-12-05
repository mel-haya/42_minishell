/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:26:34 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/04 14:26:35 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*get_export_key(char *str)
{
	char	*key;
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		key[i] = str[i];
	}
	key[i] = 0;
	return (key);
}

char	*get_export_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	if (!ft_strchr(str, '='))
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	value = ft_strdup(str + i + 1);
	return (value);
}

int	is_valid_data(char *data)
{
	int		i;

	i = 0;
	if ((ft_isalpha(data[i]) || data[i] == '_'))
	{
		while (data[++i] && data[i] != '=')
		{
			if (!ft_isalnum(data[i]) && data[i] != '=' && data[i] != '_')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	empty_export(void)
{
	t_env	*tmp;

	tmp = g_shell.env;
	while (tmp->next != NULL)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	printf("declare -x %s", tmp->name);
	if (tmp->value)
		printf("=\"%s\"", tmp->value);
	printf("\n");
	return (0);
}

int	exec_export(char **cmd)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (arr_lenght(cmd) > 1)
	{
		while (cmd[++i])
		{
			if (is_valid_data(cmd[i]))
			{
				key = get_export_key(cmd[i]);
				value = get_export_value(cmd[i]);
				add_key_value(g_shell.env, key, value);
			}
			else
			{
				printf("minishell: %s: `%s': not a valid identifier\n",
					cmd[0], cmd[i]);
				return (1);
			}
		}
		return (0);
	}
	return (empty_export());
}
