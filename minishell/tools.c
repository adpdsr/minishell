/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:29:18 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/16 14:22:49 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ignore_env(char **env, int len)
{
	if (len != 2)
	{
		ft_putendl_fd("wrong number of argument", 2);
		return (env);
	}
	ft_freetab(env);
	return (NULL);
}

char		**resize_cmd(char **cmd, char **tmp_cmd, int flag)
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

char		**rm_nl(char **env, int size)
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

static void	free_fork(char **path, char **tmp_cmd, char *paths, char *cmdp)
{
	ft_freetab(path);
	ft_strdel(&paths);
	ft_strdel(&cmdp);
	ft_freetab(tmp_cmd);
}

void		redirect_fork(char **cmd, char **env, int flag)
{
	char	*cmdp;
	char	*paths;
	char	**path;
	char	**tmp_cmd;

	cmdp = NULL;
	tmp_cmd = (char **)malloc(sizeof(char *) * (LEN(cmd) - flag + 1));
	if ((tmp_cmd = resize_cmd(cmd, tmp_cmd, flag)) && env)
	{
		paths = get_var_content(env, "PATH");
		if (paths && (path = ft_strsplit(paths, ':')))
		{
			if (path && (cmdp = find_cmdp(tmp_cmd[0], path)))
				execute_cmd(tmp_cmd, cmdp, env);
			else
				err_not_found(cmd[0], 1);
			free_fork(path, tmp_cmd, paths, cmdp);
		}
		else if (cmd[3])
			err_not_found(cmd[3], 1);
		else
			err_not_found(cmd[0], 1);
	}
	else
		do_builtin(tmp_cmd, env, 1);
}