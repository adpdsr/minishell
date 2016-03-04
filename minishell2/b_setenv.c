//
// HEADER
//

#include "minishell.h"

static char	**add_line(char **env, char **new_env, char **cmd, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;

	}
	new_env[i] = ft_strjoin(cmd[1], "=");
	new_env[i] = ft_strjoin(new_env[i], cmd[2]);
	new_env[i + 1] = NULL;
	return (new_env);
}

static char	**modif_line(char **env, char **cmd, int i)
{
	char *tmp;

	env[i] = ft_strjoin(cmd[1], "=");
	tmp = env[i];
	env[i] = ft_strjoin(tmp, cmd[2]);
	i++;
	env[i] = NULL;
	return (env);
}

char		**do_setenv(char **cmd, char **env)
{
	int i;
	int len;
	char **new_env;

	if (ft_tablen(cmd) != 3)
	{
		ft_putendl_fd("setenv must have 2 parameters", 2);
		return (NULL);
	}
	else
	{
		len = ft_tablen(env);
		if ((i = is_in(env, cmd[1])) == len || len == 0)
		{
			len = ft_tablen(env);
			if (!(new_env = (char **)malloc(sizeof(char *) * len + 2)))
				return (NULL);
			return (add_line(env, new_env, cmd, len));
		}
		else
			return (modif_line(env, cmd, i));
	}
	return (NULL);
}
