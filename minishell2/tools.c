/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:29:18 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/14 18:54:40 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ignore_env(char **env, int len)
{
	if (len != 2)
	{
		ft_putendl_fd("wrong number of argument", 2);
		return (env);
	}
	ft_freetab(env);
	return (NULL);
}

char	**resize_cmd(char **cmd, char **tmp_cmd, int flag)
{
	int	i;

	i = 0;
	while (cmd[flag])
	{
		tmp_cmd[i] = ft_strdup(cmd[flag]);
		flag++;
		i++;
	}
	tmp_cmd[i] = NULL;
	return (tmp_cmd);
}

char	**rm_nl(char **env, int size)
{
	int		i;
	int		len;
	char	**new_env;

	i = 0;
	if (size && env)
	{
		if (!(new_env = (char **)malloc(sizeof(char *) * size)))
			return (NULL);
		while (i < size - 1)
		{
			len = ft_strlen(env[i]);
			new_env[i] = ft_strndup(env[i], len);
			new_env[i][len] = '\0';
			i++;
		}
		new_env[i] = NULL;
		ft_freetab(env);
		return (new_env);
	}
	else
		return (NULL);
}

char	**redirect_setenv(char **cmd, char **env)
{
	char	*var[4];
	char	**new_env;

	var[0] = ft_strdup("setenv");
	var[1] = ft_strcdup(cmd[1], '=');
	var[2] = ft_strsub(ft_strstr(cmd[1], "="), 1, ft_strlen(cmd[1])
			- ft_strlen(var[0]) + 3);
	var[3] = NULL;
	new_env = do_setenv(var, env);
	ft_strdel(&var[0]);
	ft_strdel(&var[1]);
	ft_strdel(&var[2]);
	return (new_env);
}

void	redirect_fork(char **cmd, char **env, int flag)
{
	char	*cmdp;
	char	*paths;
	char	**path;
	char	**tmp_cmd;

	if (!(tmp_cmd = (char **)malloc(sizeof(char *) *
		(ft_tablen(cmd) - flag + 1))))
		exit(1);
	tmp_cmd = resize_cmd(cmd, tmp_cmd, flag);
	if (env)
	{
		paths = get_var_content(env, "PATH");
		if (paths && (path = ft_strsplit(paths, ':')))
		{
			if (path && (cmdp = find_cmdp(tmp_cmd[0], path)))
				execute_cmd(tmp_cmd, cmdp, env);
			else
				ft_putendl("command not found");
		}
		else
			ft_putendl("command not found");
	}
	else
		ft_putendl("command not found");
}
