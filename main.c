/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:29:00 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/27 17:00:43 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_path(char *env_path)
{
	int 	i;
	int 	cnt;
	char 	**tab;

	if (env_path)
	{
		i = 0;
		cnt = 1;
		env_path = ft_strstr(env_path, "/");
		while (env_path[i])
		{
			if (env_path[i] == ':')
				cnt++;
			i++;
		}
		if (!(tab = (char **)malloc(sizeof(char) * cnt + 1)))
			return (NULL);
		tab = ft_strsplit(env_path, ':');
		return (tab);
	}
	else
		return (NULL);
}

void	print_tab(char **tab) // test
{
	int i;
	int len;

	i = 0;
	len = tab_len(tab);
	printf("\n");
	if (*tab && tab)
	{
		while (i < len)
		{
			ft_putnbr(i);
			if (i < 10)
				ft_putchar(' ');
			ft_putchar(' ');
			ft_putchar('|');
			ft_putstr(tab[i]);
			ft_putchar('|');
			ft_putchar('\n');
			i++;
		}
		if (tab[i] == NULL)
		{
			ft_putnbr(i);
			if (i < 10)
				ft_putchar(' ');
			ft_putchar(' ');
			ft_putendl("|NULL|");
		}
	}
	else
		printf("no cpy of **env\n");
	printf("\n");
}

int		tab_len(char **tab) // ajouter a libft
{
	int len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

char	**cpy_env(char **env)
{
	int		i;
	int		len;
	char	**cpy;

	if (*env && env)
	{
		i = 0;
		len = tab_len(env);
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

// unsetenv: delete variable to unset, or return unchanger var tab if doesnt exist

char		**do_unsetenv(char **cmd, char **env)
{
	int i;
	int j;
	char **new_env;
	int is_in;

	i = 0;
	is_in = 0;
	if (tab_len(cmd) != 2)
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
		if (!(new_env = (char **)malloc(sizeof(tab_len(env) + 2))))
			return (NULL);
		while (j < i)
		{
			new_env[j] = env[j];
			j++;
		}
		while (j < tab_len(env))
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

char	**do_setenv(char **cmd, char ***env)
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
	len_cmd = tab_len(cmd);
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
		len_env = tab_len(tmp);
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

void		do_env()
{

}

void		do_cd(char **path, char **cmd, char **env)
{
	DIR 			*dir;
	char 			*tmp_path;
	struct stat		st;
	struct dirent	*ret;

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
						chdir(cmd[1]);
				}
			}
		}
		path++;
	}
}

char		*find_cmd_path(char **path, char **cmd, char **env)
{
	DIR 			*dir;
	struct dirent 	*ret;

	if (cmd)
	{
		if (ft_strcmp(cmd[0], "exit") == 0)
			exit(0);
		else if (ft_strcmp(cmd[0], "cd") == 0)
			do_cd(path, cmd, env);
		else if (ft_strcmp(cmd[0], "setenv") == 0)
			env = do_setenv(cmd, &env);
		else if (ft_strcmp(cmd[0], "unsetenv") == 0)
			env = do_unsetenv(cmd, env);
		//else if (ft_strcmp(cmd[0], "env") == 0)
		//{
		//
		//}
		else
		{
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
		}
	}
	return (NULL);
}

char	**split_cmd(char *cmd)
{
	char **splited_cmd;

	if (cmd)
	{
		splited_cmd = ft_strsplit(cmd, ' ');
		return (splited_cmd);
	}
	else
		return (NULL);
}

char	**add_path_to_cmd(char *path, char **cmd)
{
	int 	i;
	int		len_cmd;
	char 	**new_cmd;

	if (path && cmd && *cmd)
	{
		i = 0;
		len_cmd = tab_len(cmd);
		if (!(new_cmd = (char **)malloc(sizeof(char *) * len_cmd + 2)) || !len_cmd) // +1 pour new line +1 pour NULL
			return (NULL);
		new_cmd[0] = ft_strdup(path);
		while (i < len_cmd)
		{
			new_cmd[i + 1] = cmd[i];
			i++;
		}
		new_cmd[i + 1] = NULL;
		return (new_cmd);
	}
	else
		return (NULL);
}

void	exe_cmd(char **path, char **cmd, char **env)
{
	int ret;
	char *cmd_path;
	pid_t pid;

	cmd_path = NULL;
	if (cmd[0])
	{
		pid = fork();
		cmd_path = find_cmd_path(path, cmd, env);
		if (pid > 0)
			wait(0);
		else
		{
			if (cmd_path != NULL)
			{
				cmd_path = ft_strjoin(find_cmd_path(path, cmd, env), "/");
				cmd_path = ft_strjoin(cmd_path, cmd[0]);
				ret = execve(cmd_path, cmd, env);
			}
			//	else if (access(cmd[0], R_OK) == 0)
			//		execve(cmd[0], cmd, env);
			//	else
			//	{
			//		ft_putstr(cmd[0]);
			//		ft_putendl(": command not found");
			//		exit(1);
			//	}
		}
		// kill
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

char	*get_curr_path(char *path)// prompt.c
{
	int i;
	char *curr;

	if (path)
	{
		i = ft_strlen(path);
		while (path[i] != '/')
			i--;
		curr = ft_strsub(path, i + 1, ft_strlen(path));
		return (curr);
	}
	else
		return (NULL);
}

void	print_prompt(char **env) // prompt.c
{
	char *pwd;
	char *user;

	pwd = NULL;
	pwd = getcwd(pwd, 20);
	pwd = get_curr_path(pwd);
	user = extract_var_content(env, "USER");
	if (ft_strcmp(pwd, user) == 0)
		pwd = "~";
	ft_putstr(pwd);
	ft_putchar(' ');
	write(1, "$>", 3);
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
			env_cpy = cpy_env(env);
			while (*env_cpy && env_cpy)											//
			{																	//
				//path = extract_path(env_cpy[23]); 							//// ajouter pour linux
				if ((path = extract_path(ft_strstr(*env_cpy, "PATH"))) != NULL) // virer pour linux
					break ;														//
				else															//
					env_cpy++;													//
			}																	//
			print_prompt(env_cpy);
			if ((ret = get_next_line(0, &line)) == 1)
			{
				cmd = split_cmd(line);
				//	if (cmd == NULL) // useless ?
				//		main(ac, av, env);
				//		print_tab(path);
				//		print_tab(env_cpy);
				//	if (find_cmd_path(path, cmd, env_cpy) == NULL)
				//	{
				//		ft_putstr(cmd[0]);
				//		ft_putendl(": command not found");
				//		free(line);
				//		line = NULL;
				//	}
				//	else
				exe_cmd(path, cmd, env_cpy); // fork, wait
			}
		}
	}
	else
		ft_putendl_fd("minishell doesn't take any argument", 2);
	return (0);
}
