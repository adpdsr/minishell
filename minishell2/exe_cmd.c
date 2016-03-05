//
// HEADER
//

#include "minishell.h"

void	execute_cmd(char **cmd, char *cmdp, char **env)
{
	char *tmp;
	pid_t father;

	father = fork();
	if (father > 0)
		wait(0);
	else if (father == 0)
	{
		tmp = ft_strjoin(cmdp, "/");
		ft_strdel(&cmdp);
		cmdp = ft_strjoin(tmp, cmd[0]);
		ft_strdel(&tmp);
		execve(cmdp, cmd, env);
		// prog never go there
	}
	else
		ft_putendl("cannot fork");
}
