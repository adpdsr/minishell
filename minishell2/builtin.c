/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:03:39 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/14 18:55:58 by adu-pelo         ###   ########.fr       */
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

	ft_putendl("test1.0");
	if (!ft_strcmp(cmd[0], "cd"))
	{
		ft_putendl("test1.1");
		modif_env = do_cd(cmd, env);
	}
	else if (!ft_strcmp(cmd[0], "setenv"))
	{
		ft_putendl("test1.2");
		modif_env = do_setenv(cmd, env);
	}
	else if (!ft_strcmp(cmd[0], "unsetenv"))
	{
		ft_putendl("test1.3");
		modif_env = do_unsetenv(cmd, env);
	}
	else
	{
		ft_putendl("test1.4");
		modif_env = do_env(cmd, env);
	}
	ft_putendl("test1.5");
	return (modif_env);
}
