//
// HEADER
//

#include "./minishell.h"

char		**do_cd(char **cmd, char **env)
{
	DIR 			*dir;
	struct stat		st;
	struct dirent	*ret;

	if (cmd[1] && (dir = opendir(cmd[1])))
	{
		if (stat(cmd[1], &st))
			ft_putendl_fd(ft_strjoin("cd: No such file or directory: ", cmd[1]), 2);
		else if (!(S_ISDIR(st.st_mode)))
			ft_putendl_fd(ft_strjoin("cd: Not a directory: ", cmd[1]), 2);
		else if (access(cmd[1], X_OK) == -1) // acces return -1 if cant acces with X_OK (exec rights)
			ft_putendl_fd(ft_strjoin("cd: Permission denied: ", cmd[1]), 2);
		else
			chdir(cmd[1]);
	}
	else
		ft_putendl_fd(ft_strjoin("cd: No such file or directory: ", cmd[1]), 2);
	return (env);
}
