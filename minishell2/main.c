/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:05:32 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/15 17:28:37 by adu-pelo         ###   ########.fr       */
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
	int		ref;
	char	*tmp;
	char	*cmdp;

	cmdp = NULL;
	if ((ft_strstr(cmd[0], "/")))
	{
		tmp = cmd[0];
		ref = ft_strlen(cmd[0]);
		while (ref > 0 && cmd[0][ref] != '/')
			ref--;
		cmdp = ft_strsub(tmp, 0, ref);
		cmd[0] = ft_strsub(tmp, ref + 1, ft_strlen(tmp));
		ft_strdel(&tmp);
		execute_cmd(cmd, cmdp, NULL);
	}
	else if ((cmdp = find_cmdp(cmd[0], path)) != NULL)
		execute_cmd(cmd, cmdp, env);
	else
		ft_putendl("command not found");
	ft_strdel(&cmdp);
}

static char	**parse_cmd(char **env, char **cmd, char **path, char *line)
{
	cmd = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (ft_tablen(cmd) != 0)
	{
		path = get_path_tab(env, path);
		if (!(ft_strcmp(cmd[0], "exit")) && ft_tablen(cmd) == 1)
		{
			free_exit(env, cmd, path);
			exit(0);
		}
		else if (is_builtin(cmd[0]) > 0)
			env = do_builtin(cmd, env);
		else
			do_exe_cmd(env, cmd, path);
		ft_freetab(path);
	}
	if (cmd)
		ft_freetab(cmd);
	return (env);
}

// ls -l ; cd ./ ; pwd
// tab 1
// -> ls
// -> -l
// tab 2
// -> cd
// -> ./
// tab 3
// pwd

int			main(int ac, char **av, char **environ)
{
	char	*line;
	char	**cmd;
	char	**env;
	char	**path;

	signal(SIGINT, SIG_IGN);
	env = ft_tabdup(environ);
	if (ac == 1)
	{
		while (1)
		{
			cmd = NULL;
			path = NULL;
			prompt(env);
			if ((get_next_line(0, &line)) == 1)
				env = parse_cmd(env, cmd, path, line);
			else
				ft_putendl("no command");
		}
	}
	else
		ft_putendl("minishell doesn't take any argument");
	av = NULL;
	return (0);
}
