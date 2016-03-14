/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 13:42:10 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/14 11:58:40 by adu-pelo         ###   ########.fr       */
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
	ft_freetab(env);
	return (new_env);
}

static char	**modif_line(char **env, char **cmd, int i, int len)
{
	char *tmp;

	if (len == 1)
	{
		ft_freetab(env);
		return (NULL);
	}
	ft_strdel(&env[i]);
	env[i] = ft_strcat(cmd[1], "=");
	tmp = env[i];
	env[i] = ft_strjoin(tmp, cmd[2]);
	env[i + 1] = NULL;
	return (env);
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
			return (new_env);
		}
		return (modif_line(env, cmd, i, len));
	}
	ft_freetab(env);
	return (NULL);
}
