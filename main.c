/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:29:00 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/03 16:33:16 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int i;
	int len;

	i = 0;
	ft_putendl("--- PRINT ENV ---");
	len = ft_tablen(env);
	ft_putendl("---> tab_len OK");
	if (env && **env)
	{
		while (i < len)
		{
			ft_putendl(env[i]);
			i++;
		}
	}
	else
		ft_putendl("environment is empty");
	ft_putendl("--- END PRINT ENV ---");
}

char	**cpy_env(char **env)
{
	int		i;
	int		len;
	char	**cpy;

	ft_putendl("--- CPY ENV ---");
	if (**env && *env && env)
	{
		i = 0;
		len = ft_tablen(env);
		if (!(cpy = (char **)malloc(sizeof(char *) * len + 1)))
			return (NULL);
		while (i < len)
		{
			cpy[i] = ft_strdup(env[i]);
			i++;
		}
		cpy[i] = NULL;
		return (cpy);
	}
	else
		return (NULL);
}

char		*find_cmd_path(char **path, char **cmd, char **env)
{
	DIR 			*dir;
	struct dirent 	*ret;

	while (*path && path)
	{
		if ((dir = opendir(*path)))
		{
			while ((ret = readdir(dir)))
			{
				if (ft_strcmp(ret->d_name, cmd[0]) == 0)
					return (*path);
			}
		}
		path++;
	}
	return (NULL);
}

char	**split_cmd(char *cmd)
{
	char **splited_cmd;

	splited_cmd = NULL;
	if (cmd)
		splited_cmd = ft_strsplit(cmd, ' ');
	return (splited_cmd);
}

char	**add_path_to_cmd(char *path, char **cmd)
{
	int 	i;
	int		len_cmd;
	char 	**new_cmd;

	new_cmd = NULL;
	if (path && cmd && *cmd)
	{
		i = -1;
		len_cmd = ft_tablen(cmd);
		if (!(new_cmd = (char **)malloc(sizeof(char *) * len_cmd + 2)) || !len_cmd)
			return (NULL);
		new_cmd[0] = ft_strdup(path);
		while (++i < len_cmd)
			new_cmd[i + 1] = cmd[i];
		new_cmd[++i] = NULL;
	}
	return (new_cmd);
}

int		is_builtin(char *cmd)
{
	if (cmd && (!ft_strcmp(cmd, "cd")
				|| !ft_strcmp(cmd, "env")
				|| !ft_strcmp(cmd, "exit")
				|| !ft_strcmp(cmd, "setenv")
				|| !ft_strcmp(cmd, "unsetenv")))
		return (1);
	else
		return (0);
}

char	**exe_cmd(char **path, char **cmd, char **env)
{
	//int		ret;
	char	*cmd_path;
	pid_t	pid;

	//ret = -1;
	cmd_path = NULL;
	if (cmd && is_builtin(cmd[0]))
	{
		ft_putendl("--- IS BUILTIN ---");
		env = do_builtin(cmd, path, env);
	}
	else
	{
		ft_putendl("--- ISNT BUILTIN ---");
		pid = fork();
		if (pid > 0)
		{
			// parent process
			//waitpid(pid, &ret, 0);
			wait(0);
		}
		else
		{
			// child process
			ft_putendl("--- EXE NON BUILTIN CMD ---");
			//	ft_putendl(cmd[0]);
			if ((cmd_path = find_cmd_path(path, cmd, env)))
			{
				cmd_path = ft_strjoin(find_cmd_path(path, cmd, env), "/");
				cmd_path = ft_strjoin(cmd_path, cmd[0]);
			}
			else
				ft_putendl("command not found");
			execve(cmd_path, cmd, env);
		}
		return (env);
	}
	return (env);
}

char 	*extract_var_content(char **env, char *var)
{
	int		i;
	int		len_var;
	char	*content;

	i = 0;
	if (env)
	{
		printf("debug5\n");
		while (env && env[i])
		{
			printf("debug6\n");
			ft_putendl(env[i]);
			if ((ft_strstr(env[i], var)))
			{
				printf("debug7\n");
				len_var = ft_strlen(var) + 1;
				printf("debug8\n");
				content = ft_strdup(ft_strsub(env[i], len_var, ft_strlen(env[i]) - len_var));
				printf("debug9\n");
				ft_putstr("var content is: ");
				ft_putendl(content);
				return (content);
			}
			else	
				i++;
		}
	}
	return (NULL);
}

char	**extract_path(char **env)
{
	int 	i;
	int		j;
	int 	cnt;
	char	*cpy;
	char 	**tab;

	i = -1;
	j = -1;
	cnt = 1;
	cpy = NULL;
	ft_putendl("--- EXTRACTING PATH ---");
	if (env)
		cpy = extract_var_content(env, "PATH");
	if (cpy)
	{
		while (cpy[++j])
		{
			if (cpy[j] == ':')
				cnt++;
		}
		if (!(tab = (char **)malloc(sizeof(char) * cnt + 1)))
			return (NULL);
		tab = ft_strsplit(cpy, ':');
		return (tab);
	}
	return (NULL);
}

int		main(int ac, char **av, char **env)
{
	int 	ret;
	char	**cmd;
	char 	**path;
	char	*line;
	char	**env_cpy;

	ret = 0;
	line = NULL;
	if (ac == 1)
	{
		env_cpy = cpy_env(env);
		while (1)
		{
			print_env(env_cpy);
			path = NULL;
		//	env_cpy = cpy_env(env);
			ft_putendl("--- START PRINT PROMPT ---");
			print_prompt(env_cpy);
			if (((ret = get_next_line(0, &line)) == 1) && ft_strcmp(line, ""))
			{
				ft_putendl("--- GNL SUCCESS ---");
				if (line)
				{
					ft_putendl("--- LINE OK ---");
					cmd = split_cmd(line);
					ft_putendl("--- CMD OK ---");
				}
				if (cmd && env_cpy)
				{
					ft_putendl("--- CMD OK ENV OK ---");
					path = extract_path(env_cpy);
					print_env(path);
					ft_putendl("--- EXTRACT PATH OK ---");
					if (path)
					{
						ft_putendl("--- START EXE CMD ---");
						env_cpy = exe_cmd(path, cmd, env_cpy);
						ft_putendl("--- END EXE CMD ---");
					}
					else
						ft_putendl("--- NO PATH CREATED ---");
				}
				else
					ft_putendl("--- NO CMD OR ENV ---");
			}
		}
	}
	else
		ft_putendl_fd("minishell doesn't take any argument", 2);
	return (0);
}
