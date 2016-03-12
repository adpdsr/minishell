/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:05:32 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/12 18:41:00 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_env(char **env)
{
	int i;

	i = 0;
	if (env && *env)
	{
		while (env[i])
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

static int	is_builtin(char *cmd)
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

static char	*find_cmdp(char *cmd, char **path)
{
	int				i;
	int				j;
	DIR				*dir;
	struct dirent	*ret;

	if (cmd && path)
	{
		i = 0;
		j = 0;
		while (path[i])
		{
			if ((dir = opendir(path[i])))
				while ((ret = readdir(dir)))
					if (!ft_strcmp(ret->d_name, cmd))
					{
						closedir(dir);
						return (ft_strdup(path[i]));
					}
			closedir(dir);
			i++;
		}
	}
	ft_putendl("could not find cmd path");
	return (NULL);
}

char		*get_var_content(char **env, char *var)
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
				free(tmp);
				tmp = NULL;
				return (content);
			}
			i++;
		}
	}
	return (NULL);
}

int			main(int ac, char **av, char **environ)
{
	char	*line;
	char	*cmdp;
	char	**cmd;
	char	**env;
	char	*paths;
	char	**path;

	cmd = NULL;
	env = NULL;
	cmdp = NULL;
	line = NULL;
	path = NULL;
	env = ft_tabdup(environ);
	if (ac == 1)
	{
		while (1)
		{
			prompt(env);
			if ((get_next_line(0, &line)) == 1)
			{
				cmd = ft_strsplit(line, ' ');
				ft_strdel(&line);
				if (ft_tablen(cmd))
				{
					paths = get_var_content(env, "PATH");
					if (paths)
						path = ft_strsplit(paths, ':');
					else
						path = NULL;
					if (!(ft_strcmp(cmd[0], "exit")) && ft_tablen(cmd) == 1)
					{
						if (paths)
							ft_strdel(&paths);
						if (path)
							ft_freetab(path);
						if (cmd)
							ft_freetab(cmd);
						if (cmdp)
							ft_strdel(&cmdp);
						if (line)
							ft_strdel(&line);
						break ;
					}
					else if (is_builtin(cmd[0]) > 0)
						env = do_builtin(cmd, env);
					else
					{
						if ((cmdp = find_cmdp(cmd[0], path)) != NULL)
							execute_cmd(cmd, cmdp, env);
						else
							ft_putendl("command not found");
					}
					ft_strdel(&paths);
				}
				else
					ft_putendl("no command");
				if (path)
					ft_freetab(path);
				if (cmd)
					ft_freetab(cmd);
				if (cmdp)
					ft_strdel(&cmdp);
			}
		}
		ft_putendl("freeing env");
		ft_freetab(env);
	}
	else
		ft_putendl("minishell doesn't take any argument");
	av = NULL;
	return (0);
}
