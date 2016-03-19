/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 13:42:33 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/19 17:39:56 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_tilde(char **env, char **cmd)
{
	int i;

	i = -1;
	while (cmd[++i])
		if (cmd[i][0] == '~')
			cmd[i] = add_root_path(env, cmd[i]);
}

char		*find_cmdp(char *cmd, char **path)
{
	int				i;
	int				j;
	DIR				*dir;
	struct dirent	*ret;

	if (cmd && path && *path)
	{
		j = 0;
		i = -1;
		while (path[++i])
			if ((dir = opendir(path[i])))
			{
				while ((ret = readdir(dir)))
					if (!ft_strcmp(ret->d_name, cmd))
					{
						closedir(dir);
						return (ft_strdup(path[i]));
					}
				closedir(dir);
			}
	}
	return (NULL);
}

void		execute_cmd(char **cmd, char *cmdp, char **env)
{
	char	*tmp;
	pid_t	father;

	check_tilde(env, cmd);
	tmp = ft_strjoin(cmdp, "/");
	if (access(ft_strjoin(tmp, cmd[0]), X_OK) != -1)
	{
		father = fork();
		if (father > 0)
			wait(0);
		else if (father == 0)
		{
			signal(SIGINT, SIG_DFL);
			cmdp = ft_strjoin(tmp, cmd[0]);
			execve(cmdp, cmd, env);
			ft_strdel(&cmdp);
		}
		else
			ft_putendl("cannot fork");
	}
	else
		ft_putstrstr_fd(cmd[0], ": Permission denied\n", 2);
	ft_strdel(&tmp);
}