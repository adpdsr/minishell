/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:03:39 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/16 14:34:21 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_in(char **env, char *cmd)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(cmd);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], cmd, len))
			break ;
		i++;
	}
	return (i);
}

char	**do_builtin(char **cmd, char **env, int flag)
{
	char	**modif_env;

	modif_env = NULL;
	if (flag == 0)
	{
		if (!ft_strcmp(cmd[0], "cd"))
			modif_env = do_cd(cmd, env);
		else if (!ft_strcmp(cmd[0], "setenv"))
			modif_env = do_setenv(cmd, env);
		else if (!ft_strcmp(cmd[0], "unsetenv"))
			modif_env = do_unsetenv(cmd, env, 0);
		else if (!ft_strcmp(cmd[0], "env"))
			modif_env = do_env(cmd, env);
		else if (cmd[0])
			err_not_found(cmd[0], 1);
	}
	return (modif_env);
}
