//
// HEADER
//

#include "minishell.h"
#include <stdio.h> // test

void		print_env(char **env)
{
	int i;

	i = 0;
	if (env)
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
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (2);
	else if (!ft_strcmp(cmd, "env"))
		return (3);
	else if (!ft_strcmp(cmd, "setenv"))
		return (4);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (5);
	else
		return (0);
}

static char	*find_cmdp(char *cmd, char **path)
{
	int 		i;
	int		j;
	DIR		*dir;
	struct dirent 	*ret;

	if (cmd && path)
	{
		i = 0;
		j = 0;
		while (path[i])
		{
			if ((dir = opendir(path[i])))
			{
				while ((ret = readdir(dir)))
					if (!ft_strcmp(ret->d_name, cmd))
						return (ft_strdup(path[i]));
			}
			i++;
		}
	}
	else
	{
		ft_putendl("could not find cmd path");
		return (NULL);
	}
}

char	*get_var_content(char **env, char *var)
{
	int 	i;
	int 	start;
	char 	*tmp;
	char 	*content;

	if (env)
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
	else
		return (NULL);
}

static void	execute_cmd(char **cmd, char *cmdp, char **env)
{
	pid_t father;

	father = fork();
	if (father > 0)
		wait(0);
	else if (father == 0)
	{
		cmdp = ft_strcat(cmdp, "/");
		cmdp = ft_strcat(cmdp, cmd[0]);
		execve(cmdp, cmd, env);
		// prog never go there
	}
	else
		ft_putendl("cannot fork");
	ft_putendl("-----"); // test
	ft_putendl("free"); // test
	ft_putendl(cmdp); // test
	ft_putendl("-----"); // test
	ft_strdel(&cmdp);
}

int		main(int ac, char **av, char **environ)
{
	char *line;
	char *cmdp;
	char **cmd;
	char **env;
	char *patht;
	char **path;

	cmd = NULL; //
	env = NULL; //
	cmdp = NULL;//
	line = NULL;//
	path = NULL;//
	env = ft_tabdup(environ);
	if (ac == 1)
	{
		while (1)
		{
			prompt(env);
			if ((get_next_line(0, &line)) == 1)
			{
				cmd = ft_strsplit(line, ' ');
				ft_putendl("-----"); // test
				ft_putendl("free"); // test
				ft_putendl(line); // test
				ft_putendl("-----"); // test
				ft_strdel(&line);
				if (ft_tablen(cmd))
				{
					patht = get_var_content(env, "PATH");
					if (patht)
						path = ft_strsplit(patht, ':');
					if (is_builtin(cmd[0]) > 0)
						env = do_builtin(cmd, path, env);
					else
					{
						if ((cmdp = find_cmdp(cmd[0], path)) != NULL)
							execute_cmd(cmd, cmdp, env);
						else
							ft_putendl("command not found");
					}
				}
				else
					ft_putendl("no command");
				ft_putendl("-----"); // test
				ft_putendl("free"); // test
				print_env(cmd); // test
				ft_putendl("-----");
				ft_freetab(cmd); // test
			}

		}
	}
	else
		ft_putendl("minishell doesn't take any argument");
	return (0);
}