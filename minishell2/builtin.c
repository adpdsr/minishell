/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:03:39 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/12 18:33:22 by adu-pelo         ###   ########.fr       */
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

char	**do_builtin(char **cmd, char **env)
{
	char	**modif_env;

	if (!ft_strcmp(cmd[0], "cd"))
	{
		modif_env = do_cd(cmd, env);
		free(env);
		env = NULL;
	}
	else if (!ft_strcmp(cmd[0], "setenv"))
		modif_env = do_setenv(cmd, env);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		modif_env = do_unsetenv(cmd, env);
	else
		modif_env = do_env(cmd, env);
	return (modif_env);
}
