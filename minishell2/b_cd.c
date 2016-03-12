/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 11:59:04 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/12 18:31:54 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**do_cd(char **cmd, char **env)
{
	DIR			*dir;
	struct stat	st;

	if (cmd[1] && (dir = opendir(cmd[1])))
	{
		if (stat(cmd[1], &st))
			ft_putendl_fd(ft_strjoin("cd: No such file or directory: ",
						cmd[1]), 2);
		else if (!(S_ISDIR(st.st_mode)))
			ft_putendl_fd(ft_strjoin("cd: Not a directory: ", cmd[1]), 2);
		else if (access(cmd[1], X_OK) == -1)
			ft_putendl_fd(ft_strjoin("cd: Permission denied: ", cmd[1]), 2);
		else
			chdir(cmd[1]);
		closedir(dir);
	}
	else
		ft_putendl_fd(ft_strjoin("cd: No such file or directory: ", cmd[1]), 2);
	return (env);
}
