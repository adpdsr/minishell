/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 13:42:10 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/19 17:38:32 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_line(char **env, char **new_env, char **cmd, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	tmp = ft_strjoin(cmd[1], "=");
	new_env[i] = ft_strjoin(tmp, cmd[2]);
	ft_strdel(&tmp);
	new_env[i + 1] = NULL;
	return (new_env);
}

static char	**modif_line(char **env, char **cmd, int i)
{
	char *tmp;

	ft_strdel(&env[i]);
	env[i] = ft_strcat(cmd[1], "=");
	tmp = env[i];
	env[i] = ft_strjoin(tmp, cmd[2]);
	return (env);
}

char		**redirect_setenv(char **cmd, char **env)
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

char		**do_setenv(char **cmd, char **env)
{
	int		i;
	int		len;
	char	**new_env;

	if (ft_tablen(cmd) != 3)
	{
		ft_putendl_fd("setenv must have 2 parameters", 2);
		return (env);
	}
	else
	{
		len = ft_tablen(env);
		if ((i = is_in(env, cmd[1])) == len || len == 0)
		{
			if (!(new_env = (char **)malloc(sizeof(char *) * (len + 2))))
				return (NULL);
			new_env = add_line(env, new_env, cmd, len);
			ft_freetab(env);
			return (new_env);
		}
		return (modif_line(env, cmd, i));
	}
	return (NULL);
}
