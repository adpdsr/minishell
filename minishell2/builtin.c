//
// HEADER
//

#include "minishell.h"

int		is_in(char **env, char *cmd)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(cmd);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], cmd, len))
			break ;
		i++;
	}
	return (i);
}

char	**do_builtin(char **cmd, char **path, char **env)
{
	char **modif_env;

	if (!ft_strcmp(cmd[0], "cd"))
		modif_env = do_cd(cmd, env);
	else if (!ft_strcmp(cmd[0], "setenv"))
		modif_env = do_setenv(cmd, env);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		modif_env = do_unsetenv(cmd, env);
	else
		modif_env = do_env(cmd, env);
	return (modif_env);
}
