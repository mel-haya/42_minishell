#include "../execution.h"

void	exec_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
}