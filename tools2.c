/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:40:14 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/16 12:03:27 by adu-pelo         ###   ########.fr       */
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

char	*find_cmdp(char *cmd, char **path)
{
	int				i;
	int				j;
	DIR				*dir;
	struct dirent	*ret;

	if (cmd && path && *path)
	{
		j = 0;
		i = -1;
		while (path[++i])
			if ((dir = opendir(path[i])))
			{
				while ((ret = readdir(dir)))
					if (!ft_strcmp(ret->d_name, cmd))
					{
						closedir(dir);
						return (ft_strdup(path[i]));
					}
				closedir(dir);
			}
	}
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
				start = ft_strlen(var) + 1;
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

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (2);
	else if (!ft_strcmp(cmd, "setenv"))
		return (3);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (4);
	else
		return (0);
}

void	free_exit(char **env, char **cmd, char **path)
{
	ft_freetab(path);
	ft_freetab(cmd);
	ft_freetab(env);
}
