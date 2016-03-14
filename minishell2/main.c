/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:05:32 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/14 18:56:02 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path_tab(char **env, char **path)
{
	char	*paths;

	paths = NULL;
	paths = get_var_content(env, "PATH");
	if (paths)
	{
		path = ft_strsplit(paths, ':');
		ft_strdel(&paths);
		return (path);
	}
	return (NULL);
}

static void	do_exe_cmd(char **env, char **cmd, char **path)
{
	char	*cmdp;

	cmdp = NULL;
	if ((cmdp = find_cmdp(cmd[0], path)) != NULL)
		execute_cmd(cmd, cmdp, env);
	else
		ft_putendl("command not found");
	ft_strdel(&cmdp);
}

static void	free_exit(char **env, char **cmd, char **path)
{
	ft_freetab(path);
	ft_freetab(cmd);
	ft_freetab(env);	
}

static void	parse_cmd(char **env, char **cmd, char **path, char *line)
{
	cmd = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (ft_tablen(cmd))
	{
		path = get_path_tab(env, path);
		if (!(ft_strcmp(cmd[0], "exit")) && ft_tablen(cmd) == 1)
		{
			free_exit(env, cmd, path);
			exit(0);
		}
		else if (is_builtin(cmd[0]) > 0)
		{
			ft_putendl("test1");
			env = do_builtin(cmd, env);
			ft_putendl("test2");
		}
		else
			do_exe_cmd(env, cmd, path);
		ft_putendl("test3");
		ft_freetab(path);
		ft_putendl("test4");
	}
}

int			main(int ac, char **av, char **environ)
{
	char	*line;
	char	**cmd;
	char	**env;
	char	**path;

	ft_putendl("test0.0");
	env = ft_tabdup(environ);
	ft_putendl("test0.1");
	if (ac == 1)
	{
		while (1)
		{
			ft_putendl("test0.2");
			cmd = NULL;
			path = NULL;
			ft_putendl("test0.3");
			prompt(env);
			if ((get_next_line(0, &line)) == 1)
			{
				ft_putendl("test0.4");
				parse_cmd(env, cmd, path, line);
			}
			else
				ft_putendl("no command");
			ft_putendl("test0.5");
		}
	}
	else
		ft_putendl("minishell doesn't take any argument");
	av = NULL;
	return (0);
}
