/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unsetenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:02:42 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/12 18:36:22 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_new_env(char **env, char **new_env, int i, int len)
{
	int j;

	j = 0;
	while (j < i)
	{
		new_env[j] = ft_strdup(env[j]);
		j++;
	}
	while (j < len && env[j + 1])
	{
		new_env[j] = ft_strdup(env[j + 1]);
		j++;
	}
	new_env[j] = NULL;
	ft_freetab(env);
	return (new_env);
}

char		**do_unsetenv(char **cmd, char **env)
{
	int		i;
	int		len;
	char	**new_env;

	i = 0;
	len = ft_tablen(env);
	if (ft_tablen(cmd) != 2)
		ft_putendl("unsetenv: need one argument");
	else if ((i = is_in(env, cmd[1])) != len && len > 0)
	{
		if (len == 1)
		{
			ft_freetab(env);
			return (NULL);
		}
		if (!(new_env = (char **)malloc(sizeof(char *) * (len))))
			exit(1);
		return (create_new_env(env, new_env, i, len));
	}
	else
		ft_putendl("unsetenv: envrionment unchanged");
	ft_putendl("in do_unsetenv");
	return (env);
}
