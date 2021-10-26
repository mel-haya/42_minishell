#include "../execution.h"

void	exec_env(char **cmd)
{
	t_env	*tmp;

	if (arr_lenght(cmd) == 1)
	{
		tmp = g_shell.env;
		while (tmp->next != NULL)
		{
			printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
		printf("%s%s\n", tmp->name, tmp->value);
	}
}