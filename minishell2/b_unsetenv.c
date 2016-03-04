//
// HEADER
//

#include "./minishell.h"
#include <stdio.h>

char		**do_unsetenv(char **cmd, char **env)
{
	int i;
	int j;
	int len;
	char **new_env;

	len = ft_tablen(env) - 1;
	if (ft_tablen(cmd) != 2)
		ft_putendl("unsetenv: need one argument");
	else if ((i = is_in(env, cmd[1])) != 1)
	{
		j = 0;
		if (!(new_env = (char **)malloc(sizeof(char *) * ft_tablen(env))))
		{
			ft_putendl("malloc failed");
			return (env);
		}
		while (j < i)
		{
			new_env[j] = ft_strdup(env[j]);
			j++;
		}
		while (j < len)
		{
			new_env[j] = ft_strdup(env[j + 1]);
			j++;
		}
		new_env[j] = NULL;
		// free env !
		return (new_env);
	}
	else
		ft_putendl("unsetenv: envrionment unchanged");
	return (env);
}
