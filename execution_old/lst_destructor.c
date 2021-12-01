#include "execution.h"

void	exit_err(char *msg, char *output, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(msg, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(output, fd);
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
