/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 11:59:32 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/21 16:34:03 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**do_rmnl_opt(char **cmd, char **env, char **tmp_env)
{
	int len;

	len = ft_tablen(cmd);
	if (len == 2)
	{
		ft_freetab(tmp_env);
		return (rm_nl(env, ft_tablen(env) + 1));
	}
	else if (len > 2)
	{
		tmp_env = rm_nl(tmp_env, ft_tablen(env) + 1);
		redirect_fork(cmd, tmp_env, 2);
	}
	ft_freetab(tmp_env);
	return (env);
}

static char	**do_unset_opt(char **cmd, char **env, char **tmp_env)
{
	int len;

	len = ft_tablen(cmd);
	if (len == 2)
		ft_putendl_fd("wrong number of argument", 2);
	else if (len == 3)
		return (do_unsetenv(++cmd, env, 1));
	else if (len > 3)
	{
		tmp_env = do_unsetenv(&cmd[1], tmp_env, 1);
		redirect_fork(cmd, tmp_env, 3);
	}
	ft_freetab(tmp_env);
	return (env);
}

static char	**do_ignore_opt(char **cmd, char **env, char **tmp_env)
{
	int len;

	len = ft_tablen(cmd);
	if (len == 2)
	{
		ft_freetab(tmp_env);
		return (ignore_env(env, len));
	}
	else if (len > 2)
		redirect_fork(cmd, NULL, 2);
	ft_freetab(tmp_env);
	return (env);
}

static char	**do_equal_opt(char **cmd, char **env, char **tmp_env)
{
	int len;

	len = ft_tablen(cmd);
	if (len == 2)
	{
		ft_freetab(tmp_env);
		return (redirect_setenv(cmd, env));
	}
	else if (len > 2)
	{
		tmp_env = redirect_setenv(cmd, tmp_env);
		redirect_fork(cmd, tmp_env, 2);
	}
	ft_freetab(tmp_env);
	return (env);
}

char		**do_env(char **cmd, char **env)
{
	char	**tmp_env;

	if (ft_tablen(cmd) == 1)
	{
		print_env(env);
		return (env);
	}
	if (env)
		tmp_env = ft_tabdup(env);
	if (ft_sscmp(cmd[1], "-0", "--null"))
		return (do_rmnl_opt(cmd, env, tmp_env));
	else if (ft_sscmp(cmd[1], "-u", "--unset"))
		return (do_unset_opt(cmd, env, tmp_env));
	else if (ft_ssscmp(cmd[1], "-", "-i", "--ignore-environment"))
		return (do_ignore_opt(cmd, env, tmp_env));
	else if (ft_cntc(cmd[1], '=') == 1)
		return (do_equal_opt(cmd, env, tmp_env));
	else if (!ft_strcmp(cmd[1], "--version"))
		ft_putendl("version 1.0 made by adu-pelo");
	else
		ft_putendl_fd("option not found", 2);
	ft_freetab(tmp_env);
	return (env);
}
