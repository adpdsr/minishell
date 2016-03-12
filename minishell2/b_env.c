/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 11:59:32 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/12 18:38:21 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**rm_nl(char **env, int size)
{
	int		i;
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
		return (new_env);
	}
	else
		return (NULL);
}

static char	**redirect_setenv(char **cmd, char **env)
{
	char	*var[4];
	char	**new_env;

	var[0] = ft_strdup("setenv");
	var[1] = ft_strcdup(cmd[1], '=');
	printf("strsub len is = %lu\n", ft_strlen(cmd[1]) - ft_strlen(var[0]));
	var[2] = ft_strsub(ft_strstr(cmd[1], "="), 1, ft_strlen(cmd[1])
			- ft_strlen(var[0]) + 3);
	var[3] = NULL;
	new_env = do_setenv(var, env);
	ft_strdel(&var[0]);
	ft_strdel(&var[1]);
	ft_strdel(&var[2]);
	return (new_env);
}

static char	**ignore_env(char **env, int len)
{
	if (len != 2)
	{
		ft_putendl_fd("wrong number of argument", 2);
		return (env);
	}
	ft_freetab(env);
	return (NULL);
}

char		**do_env(char **cmd, char **env)
{
	int		len;

	len = ft_tablen(cmd);
	if (len > 3 || len == 1)
	{
		if (len > 3)
			ft_putendl_fd("wrong number of argument", 2);
		else
			print_env(env);
		return (env);
	}
	else if (ft_sscmp(cmd[1], "-0", "--null"))
		return (rm_nl(env, ft_tablen(env) + 1));
	else if (ft_sscmp(cmd[1], "-u", "--unset"))
	{
		if (cmd[2])
			return (do_unsetenv(++cmd, env));
		ft_putendl_fd("wrong number of argument", 2);
		return (env);
	}
	else if (ft_ssscmp(cmd[1], "-", "-i", "--ignore-environment"))
		return (ignore_env(env, len));
	else if (cmd[1] && ft_cntc(cmd[1], '=') == 1)
	{
		if (!cmd[2])
			return (redirect_setenv(cmd, env));
		ft_putendl_fd("wrong number of argument", 2);
	}
	else if (cmd[1] && !ft_strcmp(cmd[1], "--version"))
		ft_putendl("version 1.0 made by adu-pelo");
	else
		ft_putendl_fd("option not found", 2);
	return (env);
}
