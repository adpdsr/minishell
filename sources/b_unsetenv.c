/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unsetenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:02:42 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/21 15:46:50 by adu-pelo         ###   ########.fr       */
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

void		err_not_found(char *cmd, int flag)
{
	if (flag == 1)
		ft_putstr_fd("command ", 2);
	else if (flag == 2)
		ft_putstr_fd("unsetenv: var ", 2);
	color(RED, cmd);
	color(RESET, " not found\n");
}

static char	**unset(char **env, int len, int i)
{
	char	**new_env;

	new_env = NULL;
	if (len == 1)
	{
		ft_freetab(env);
		return (NULL);
	}
	if (!(new_env = (char **)malloc(sizeof(char *) * (len))))
		exit(1);
	return (create_new_env(env, new_env, i, len));
}

char		**do_unsetenv(char **cmd, char **env, int flag)
{
	int		i;
	int		len;

	i = 0;
	len = ft_tablen(env);
	if (ft_tablen(cmd) != 2 && flag == 0)
		ft_putendl_fd("unsetenv: need one argument", 2);
	else if ((i = is_in(env, cmd[1])) != len && len > 0)
		return (unset(env, len, i));
	else if (!cmd[2])
		err_not_found(cmd[1], 2);
	else if (flag == 1)
	{
		if (!get_var_content(env, cmd[1]))
			err_not_found(cmd[1], 2);
		else
			ft_putendl_fd("unsetenv: too many arguments", 2);
	}
	else if (flag == 0)
		err_not_found(cmd[1], 2);
	return (env);
}
