#include "../execution.h"

int		filter_input(char *str)
{
	int		i;
	
	i = -1;
	if (str && ft_isdigit(str[0]))
		return (0);
	while (str && str[++i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

void	delete_node(t_env *lst, t_env *target)
{
	t_env	*tmp;
	t_env	*left;
	t_env	*right;

	tmp = lst;
	if (target == tmp)
	{
		lst = tmp->next;
		free(tmp);
	}
	else
	{
		while (tmp->next != NULL)
		{
			if (target == tmp->next)
			{
				left = tmp;
				tmp = tmp->next;
				right = tmp->next;
				free(tmp->name);
				free(tmp->value);
				free(tmp);
				left->next = right;
				break;
			}
			tmp = tmp->next;
		}
	}
}

void	exec_unset(char **cmd)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = g_shell.env;
	while (cmd[++i])
	{
		if (filter_input(cmd[i]))
		{
			while (tmp->next != NULL)
			{
				if (!ft_strncmp(cmd[i], tmp->name, ft_strlen(cmd[i])))
					delete_node(g_shell.env, tmp);
				tmp = tmp->next;
			}
			if (ft_strncmp(cmd[i], tmp->value, ft_strlen(cmd[i])))
				delete_node(g_shell.env, tmp);
		}
		else
			printf("minishell: %s: `%s': not a valid identifier\n", cmd[0], cmd[i]);
	}
}