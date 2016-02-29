/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:29:00 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/29 11:36:12 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**do_unsetenv(char **cmd, char **env)
{
	int i;
	int j;
	char **new_env;
	int is_in;

	i = 0;
	is_in = 0;
	print_env(cmd);
	if (ft_tablen(cmd) != 2)
	{
		ft_putendl("unsetenv: need one argument");
		return (NULL);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], cmd[1], ft_strlen(cmd[1])) == 0)
		{
			is_in = 1;
			break ;
		}
		i++;
	}
	if (is_in == 1)
	{
		j = 0;
		if (!(new_env = (char **)malloc(sizeof(ft_tablen(env) + 2))))
			return (NULL);
		while (j < i)
		{
			new_env[j] = env[j];
			j++;
		}
		while (j < ft_tablen(env)) // save res of tablen in var
		{
			new_env[j] = env[j + 1];
			j++;
		}
		new_env[j] = NULL;
		printf("|%s| deleted\n", cmd[1]);
		return (new_env);
	}
	else
	{
		ft_putendl("no var to unset, returning original tab");
		return (env);
	}
}

static char	**do_setenv(char **cmd, char ***env)
{
	int i;
	int j;
	int k;
	int len_cmd;
	int len_env;
	int len_new_var;
	char **tmp;
	char **new_env;

	k = 0;
	len_cmd = ft_tablen(cmd);
	len_new_var = ft_strlen(cmd[0]);
	tmp = *env;
	if (!tmp) // secu
		return (NULL);
	if (len_cmd != 3)
	{
		ft_putendl_fd("setenv must have 2 parameters", 2);
		return (NULL);
	}
	else
	{
		i = 0;
		j = 0;
		len_env = ft_tablen(tmp);
		while (tmp && *tmp)
		{
			if (ft_strstr(*tmp, cmd[1])) // si occurence trouvee
			{
				i = 1;
				break ;
			}
			tmp++;
			k++;
		}
		tmp = *env;
		if (i == 0) // si la variable a ajouter n'existe pas deja, on la cree
		{
			ft_putendl("occurence not found\n");
			if (!(new_env = (char **)malloc(sizeof(char *) * len_env + 2)))
				return (NULL);
			while (j < len_env)
			{
				new_env[j] = ft_strdup(tmp[j]);
				j++;
			}
			new_env[j] = ft_strjoin(cmd[1], "=");
			new_env[j] = ft_strjoin(new_env[j], cmd[2]);
			new_env[j + 1] = NULL;
			printf("new VAR created: |%s|\n", new_env[j]);
			return (new_env);
		}
		else if (i == 1) // si variable existe deja -> modifie
		{
			ft_putendl("occurence found\n");
			tmp[k] = ft_strjoin(cmd[1], "=");
			tmp[k] = ft_strjoin(tmp[k], cmd[2]);
			printf("old VAR replaced by: |%s|\n", tmp[k]);
			return (tmp);
		}
	}
	return (NULL);
}

static char		**do_env(char **cmd, char **env)
{
	int len;

	len = ft_tablen(cmd);
	if (len > 3)
	{
		ft_putendl_fd("wrong number of argument", 2);
		return (env);
	}
	if (len == 1)
	{
		print_env(env);
		return (env);
	}
	else if (!ft_strcmp(cmd[1], "-u") || !ft_strcmp(cmd[1], "--unset"))
	{
		if (cmd[2])
			return (do_unsetenv(++cmd, env));
		else
		{
			ft_putendl_fd("wrong number of argument", 2);
			return (env);
		}
	}
	else if (!ft_strcmp(cmd[1], "-") || !ft_strcmp(cmd[1], "-i") || ft_strcmp(cmd[1], "--ignore-environment"))
	{
		ft_putendl("environment deleted");
		return (NULL);
	}
	else
	{
		ft_putendl_fd("option not found", 2);
		return (NULL);
	}
	// handle args NOM=VALEUR
}

static char		**do_cd(char **path, char **cmd, char **env)
{
	DIR 			*dir;
	char 			*tmp_path;
	struct stat		st;
	struct dirent	*ret;

	//ft_putstr("\nres = ");
	//ft_putendl(extract_var_content(env, "HOME"));
	while (*path && path)
	{
		if ((dir = opendir(*path)))
		{
			while ((ret = readdir(dir)))
			{
				if (ft_strcmp(ret->d_name, cmd[0]) == 0)
				{
					tmp_path = *path;
					tmp_path = ft_strjoin(tmp_path, "/");
					tmp_path = ft_strjoin(tmp_path, cmd[0]);
					if (cmd[1] && stat(cmd[1], &st))
						ft_putendl_fd(ft_strjoin("cd: No such file or directory: ", cmd[1]), 2);
					else if (cmd[1] && !(S_ISDIR(st.st_mode)))
						ft_putendl_fd(ft_strjoin("cd: Not a directory: ", cmd[1]), 2);
					else if (cmd[1] && access(cmd[1], X_OK) == -1)
						ft_putendl_fd(ft_strjoin("cd: Permission denied: ", cmd[1]), 2);
					else
					{
						ft_putstr("chdir(cmd[1]) = ");
						ft_putendl(cmd[1]);
						chdir(cmd[1]);
					}
				}
			}
		}
		path++;
	}
	return (env);
}

char	**do_builtin(char **cmd, char **path, char **env)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		env = do_cd(path, cmd, env);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		env = do_setenv(cmd, &env);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		env = do_unsetenv(cmd, env);
	else
	{
		ft_putendl("----- DO_ENV -----");
		env = do_env(cmd, env);
	}
	return (env);
}
