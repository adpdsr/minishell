//
// HEADER
//

#include "minishell.h"

static char	**rm_nl(char **env, int size)
{
	int	i;
	size_t	len;
	char	**new_env;

	i = 0;
	if (size && env)
	{
		if (!(new_env = (char **)malloc(sizeof(char *) * (size))))
			return (NULL);
		while (i < size - 1)
		{
			len = ft_strlen(env[i]);
			new_env[i] = ft_strndup(env[i], len);
			new_env[i][len] = '\0';
			i++;
		}
		new_env[i] = NULL;
		// free env
		return (new_env);
	}
	else
		return (NULL);
}

static int	cmp2(char *cmd, char *opt1, char *opt2)
{
	if (!ft_strcmp(cmd, opt1) || !ft_strcmp(cmd, opt2))
		return (1);
	return (0);
}

static int	cmp3(char *cmd, char *opt1, char *opt2, char *opt3)
{
	if (!ft_strcmp(cmd, opt1) || !ft_strcmp(cmd, opt2) || !ft_strcmp(cmd, opt3))
		return (1);
	return (0);
}

char		**do_env(char **cmd, char **env)
{
	char	*var[4];
	char	*content;
	int	len;

	len = ft_tablen(cmd);
	if (len > 3 || len == 1)
	{
		if (len > 3)
			ft_putendl_fd("wrong number of argument", 2);
		else
			print_env(env);
		return (env);
	}
	else if (cmp2(cmd[1], "-0", "--null"))
		return (rm_nl(env, ft_tablen(env) + 1));
	else if (cmp2(cmd[1], "-u", "--unset"))
	{
		if (cmd[2])
			return (do_unsetenv(++cmd, env));
		ft_putendl_fd("wrong number of argument", 2);
		return (env);
	}
	else if (cmp3(cmd[1], "-", "-i", "--ignore-environment"))
	{
		if (len != 2)
		{
			ft_putendl_fd("wrong number of argument", 2);
			return (env);
		}
		ft_freetab(env);
		return (NULL);
	}
	else if (cmd[1] && ft_cntc(cmd[1], '=') == 1)
	{
		ft_putendl("ok");
		if (!cmd[2])
		{
			var[0] = ft_strdup("setenv");
			var[1] = ft_strcdup(cmd[1], '=');
			var[2] = ft_strsub(ft_strstr(cmd[1], "="), 1, ft_strlen(cmd[1]) - ft_strlen(var[0]));
			var[3] = NULL;
			return (do_setenv(var, env));
		}
		ft_putendl_fd("wrong number of argument", 2);
	}
	ft_putendl_fd("option not found", 2);
	return (env);
	// exe cmd in modified env
}
