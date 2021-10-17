#include "execution.h"

void	exit_err(char *msg, int status, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(": command not found", fd);
	exit(status);
}

// void	free_lst(t_env **lst)
// {
// 	t_env	*tmp;

// 	if (lst)
// 	{
// 		while (*lst)
// 		{
// 			tmp = (*lst)->next;
// 			free((*lst)->key);
// 			free((*lst)->value);
// 			free(*lst);
// 			*lst = tmp;
// 		}
// 		*lst = NULL;
// 	}
// }
