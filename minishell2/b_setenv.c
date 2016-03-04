//
// HEADER
//

#include "./minishell.h"
#include <stdio.h>

char	**do_setenv(char **cmd, char **env)
{
	int i;
	int j;
	int len;
	char *tmp;
	char **new_env;

	if (ft_tablen(cmd) != 3)
	{
		ft_putendl_fd("setenv must have 2 parameters", 2);
		return (NULL);
	}
	else
	{
		j = 0;
		if ((i = is_in(env, cmd[1])) == len) // si variable n'existe pas -> creation
		{
			len = ft_tablen(env);
			if (!(new_env = (char **)malloc(sizeof(char *) * len + 2)))
				return (NULL);
			while (j < len)
			{
				new_env[j] = ft_strdup(env[j]);
				j++;
			}
			new_env[j] = ft_strjoin(cmd[1], "=");
			new_env[j] = ft_strjoin(new_env[j], cmd[2]);
			new_env[j + 1] = NULL;
			return (new_env);
		}
		else // si variable existe deja -> modifie
		{
			env[i] = NULL; // strdel
			env[i] = ft_strjoin(cmd[1], "=");
			tmp = env[i];
			env[i] = ft_strjoin(tmp, cmd[2]);
			return (env);
		}
	}
	return (NULL);
}
