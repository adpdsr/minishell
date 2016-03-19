/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:29:18 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/19 17:27:32 by adu-pelo         ###   ########.fr       */
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

static void	redirect_error(char **cmd)
{
	if (cmd[3])
		err_not_found(cmd[3], 1);
	else
		err_not_found(cmd[0], 1);
}

void		redirect_fork(char **cmd, char **env, int flag)
{
	char	*cmdp;
	char	*paths;
	char	**path;
	char	**tmp_cmd;

	cmdp = NULL;
	tmp_cmd = (char **)malloc(sizeof(char *) * (LEN(cmd) - flag + 1));
	paths = get_var_content(env, "PATH=");
	if (paths)
		path = ft_strsplit(paths, ':');
	if ((tmp_cmd = resize_cmd(cmd, tmp_cmd, flag)) && env)
	{
		if (!paths || !path)
			redirect_error(cmd);
		else if (path && (cmdp = find_cmdp(tmp_cmd[0], path)))
			execute_cmd(tmp_cmd, cmdp, env);
		else
			ft_putendl_fd("command not found", 2);
		free_fork(path, tmp_cmd, paths, cmdp);
	}
	else if (!env)
		err_not_found(cmd[2], 1);
	else
		do_builtin(tmp_cmd, env, path, 1);
}
