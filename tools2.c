/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:40:14 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/19 17:03:00 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int i;

	i = 0;
	if (env && *env)
	{
		while (env && env[i])
		{
			ft_putnbr(i);
			if (i < 10)
				ft_putchar(' ');
			ft_putchar(' ');
			ft_putendl(env[i]);
			i++;
		}
	}
	else
		ft_putendl("env: environment is empty");
}

char	**rm_nl(char **env, int size)
{
	int		i;
	int		len;
	char	**new_env;

	i = 0;
	if (size && env)
	{
		if (!(new_env = (char **)malloc(sizeof(char *) * size)))
			return (NULL);
		while (i < size - 1)
		{
			len = ft_strlen(env[i]);
			new_env[i] = ft_strndup(env[i], len);
			new_env[i][len] = '\0';
			i++;
		}
		new_env[i] = NULL;
		ft_freetab(env);
		return (new_env);
	}
	else
		return (NULL);
}

char	*get_var_content(char **env, char *var)
{
	int		i;
	int		start;
	char	*tmp;
	char	*content;

	if (env && *env)
	{
		i = 0;
		while (env[i])
		{
			if (!ft_strncmp(env[i], var, ft_strlen(var)))
			{
				start = ft_strlen(var);
				tmp = ft_strsub(env[i], start, ft_strlen(env[i]) - start);
				content = ft_strdup(tmp);
				ft_strdel(&tmp);
				return (content);
			}
			i++;
		}
		return (NULL);
	}
	return (NULL);
}

void	free_exit(char **env, char **cmd, char **path)
{
	if (path && *path)
		ft_freetab(path);
	if (cmd && *cmd)
		ft_freetab(cmd);
	if (env && *env)
		ft_freetab(env);
}

void	free_fork(char **path, char **tmp_cmd, char *paths, char *cmdp)
{
	if (path && *path)
		ft_freetab(path);
	if (paths)
		ft_strdel(&paths);
	if (cmdp)
		ft_strdel(&cmdp);
	if (tmp_cmd && *tmp_cmd)
		ft_freetab(tmp_cmd);
}
