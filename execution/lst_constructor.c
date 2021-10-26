#include "execution.h"

t_env	*init_node(char *key, char *value)
{
	t_env	*lst;

	lst = (t_env *)malloc(sizeof(t_env));
	lst->name = key;
	lst->value = value;
	lst->next = NULL;
	return (lst);
}

t_env	*get_lastnode(t_env *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

void	add_node(t_env **lst, t_env *new_node)
{
	if (*lst == NULL)
		*lst = new_node;
	else
		get_lastnode(*lst)->next = new_node;
}
