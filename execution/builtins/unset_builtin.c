/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:26:53 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/11 00:57:22 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	filter_input(char *str)
{
	int		i;

	i = -1;
	if (str && ft_isdigit(str[0]))
		return (0);
	while (str && str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

void	free_values(t_env *lst)
{
	free(lst->name);
	lst->name = NULL;
	free(lst->value);
	lst->value = NULL;
	free(lst);
	lst = NULL;
}

void	delete_node(t_env *target)
{
	t_env	*tmp;
	t_env	*left;
	t_env	*right;

	tmp = g_shell.env;
	if (target == tmp)
	{
		g_shell.env = g_shell.env->next;
		free_values(tmp);
		return ;
	}
	while (tmp->next != NULL)
	{
		if (target == tmp->next)
		{
			left = tmp;
			tmp = tmp->next;
			right = tmp->next;
			free_values(tmp);
			left->next = right;
			break ;
		}
		tmp = tmp->next;
	}
}

void	unset_element(char *element)
{
	t_env	*tmp;

	tmp = g_shell.env;
	while (tmp)
	{
		if (!ft_strncmp(element, tmp->name, ft_strlen(element)
				+ ft_strlen(tmp->name)))
		{
			delete_node(tmp);
			break ;
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}

int	exec_unset(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (filter_input(cmd[i]))
			unset_element(cmd[i]);
		else
		{
			export_err(cmd[0], cmd[1]);
			return (1);
		}
	}
	return (0);
}
