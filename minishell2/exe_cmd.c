//
// HEADER
//

#include "minishell.h"

void	execute_cmd(char **cmd, char *cmdp, char **env)
{
	pid_t father;

	father = fork();
	if (father > 0)
		wait(0);
	else if (father == 0)
	{
		cmdp = ft_strcat(cmdp, "/");
		cmdp = ft_strcat(cmdp, cmd[0]);
		execve(cmdp, cmd, env);
		// prog never go there
	}
	else
		ft_putendl("cannot fork");
	ft_putendl("-----"); // test
	ft_putendl("free"); // test
	ft_putendl(cmdp); // test
	ft_putendl("-----"); // test
	ft_strdel(&cmdp);
}
