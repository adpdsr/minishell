/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:29:00 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/29 11:37:56 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env) // test
{
	int i;
	int len;

	i = -1;
	len = ft_tablen(env);
	if (*env && env)
		while (++i < len)
			ft_putendl(env[i]);
	else
		ft_putendl("environment is empty");
}

char	**cpy_env(char **env)
{
	int		i;
	int		len;
	char	**cpy;

	if (*env && env)
	{
		i = -1;
		len = ft_tablen(env);
		if (!(cpy = (char **)malloc(sizeof(char *) * len + 1)))
			return (NULL);
		while (++i < len)
			cpy[i] = ft_strdup(env[i]);
		cpy[++i] = NULL;
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
	if (cmd && (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "env")
				|| !ft_strcmp(cmd, "setenv") || !ft_strcmp(cmd, "unsetenv")))
		return (1);
	else
		return (0);
}

void	exe_cmd(char **path, char **cmd, char **env)
{
	int ret;
	char *cmd_path;
	pid_t pid;

	pid = fork();
	cmd_path = NULL;
	if (pid > 0)
	{
		//
		wait(0);
	}
	else
	{
		if (is_builtin(cmd[0]))
			env = do_builtin(cmd, path, env);
		else if ((cmd_path = find_cmd_path(path, cmd, env)))
		{
			cmd_path = ft_strjoin(find_cmd_path(path, cmd, env), "/");
			cmd_path = ft_strjoin(cmd_path, cmd[0]);
		}
		else
			ft_putendl("command nor found");
		ret = execve(cmd_path, cmd, env);
	}
}

char 	*extract_var_content(char **env, char *var)
{
	int i;
	int len_var;
	char *content;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], var))
		{
			len_var = ft_strlen(var) + 1;
			content = ft_strdup(ft_strsub(env[i], len_var, ft_strlen(env[i]) - len_var));
			return (content);
		}	
		i++;
	}
	return (NULL);
}

char	**extract_path(char **env)
{
	int 	i;
	int		j;
	int 	cnt;
	char 	**tab;

	i = -1;
	j = -1;
	cnt = 1;
	while (env && env[++i])
	{
		if (ft_strstr(env[i], "PATH="))
		{
			if ((env[i] = ft_strstr(env[i], "/")))
			{
				while (env[++j])
				{
					if (env[i][j] == ':')
						cnt++;
				}
				if (!(tab = (char **)malloc(sizeof(char) * cnt + 1)))
					return (NULL);
				tab = ft_strsplit(env[i], ':');
				return (tab);
			}
		}
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
		while (1)
		{
			print_prompt(env_cpy);
			env_cpy = cpy_env(env); // ?? where
			if (((ret = get_next_line(0, &line)) == 1) && ft_strcmp(line, ""))
			{
				if (line)
					cmd = split_cmd(line);
				if (!ft_strcmp(cmd[0], "exit"))
				{
					exit(0);
				}
				else if (cmd && env_cpy)
				{
					path = extract_path(env_cpy);
					exe_cmd(path, cmd, env_cpy);
				}
			}
		}
	}
	else
		ft_putendl_fd("minishell doesn't take any argument", 2);
	return (0);
}
