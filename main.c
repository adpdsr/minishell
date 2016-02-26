/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:29:00 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/26 19:36:01 by adu-pelo         ###   ########.fr       */
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
		printf("extract path: %s\n", env_path);
		while (env_path[i])
		{
			if (env_path[i] == ':')
				cnt++;
			i++;
		}
		printf("malloc size = %d\n", cnt + 1); // test
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

int		tab_len(char **tab)
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
		printf("malloc size = %d\n", len + 1); // test
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

char		**do_setenv(char **cmd, char ***env)
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
	ft_putendl("\n----- DO SETENV -----\n");
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
	print_tab(*env);
	return (NULL);
}

void		do_cd(char **path, char **cmd, char **env)
{
	DIR 			*dir;
	char 			*tmp_path;
	struct stat		st;
	struct dirent	*ret;

	ft_putendl("\n----- DO CD -----\n");
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
					if (cmd[1] && stat(cmd[1], &st)) // != 0 = fail to get stat
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
		{
			ft_putendl("exit cmd detected");
			exit(0);
		}
		else if (ft_strcmp(cmd[0], "cd") == 0)
		{
			ft_putendl("cd cmd detected");
			do_cd(path, cmd, env);
		}
		else if (ft_strcmp(cmd[0], "setenv") == 0)
		{
			ft_putendl("setenv cmd detected");
			env = do_setenv(cmd, &env);
		}
		//else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		//{
		//
		//}
		// etc...
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
		ft_putstr("\n----- TAB CONTAINING SPLITED CMD -----\n");
		print_tab(splited_cmd);
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
		printf("new_cmd[0] = %s\n", ft_strdup(path));
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
	ft_putendl("----- EXEC CMD -----\n");
	if (cmd[0])
	{
		pid = fork();
		cmd_path = find_cmd_path(path, cmd, env);
		if (pid > 0)
		{
			ft_putstr("son pid |");
			ft_putnbr((int)pid);
			ft_putendl("|\n");
			wait(0);
		}
		else
		{
			if (cmd_path != NULL)
			{
				cmd_path = ft_strjoin(find_cmd_path(path, cmd, env), "/");
				cmd_path = ft_strjoin(cmd_path, cmd[0]);
				ret = execve(cmd_path, cmd, env);
			}
			//else if (access(cmd[0], R_OK) == 0)
			//	execve(cmd[0], cmd, env);
			else
				ft_putendl("execve failed");
			exit(1);
		}
	}
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

	print_tab(env); // test
	ft_putstr("----- CPY OF ORIGINAL ENV TAB -----\n\n");
	env_cpy = cpy_env(env);
	print_tab(env_cpy); // test

	ft_putstr("----- CPY OF PATH CONTAINED IN PATH ENV_VAR PATH -----\n\n");
		while (*env_cpy && env_cpy)					//
		{								//
	//path = extract_path(env_cpy[23]); 					//// ajouter pour linux
		printf("strstr = %s\n", ft_strstr(*env_cpy, "PATH"));		//
		if ((path = extract_path(ft_strstr(*env_cpy, "PATH"))) != NULL) // virer pour linux
			break ;							//
		else								//
			env_cpy++;						//
		}								//
	print_tab(path); // test

	/* affichage du promp, on recupere la cmd et on la traite (verif + exe) */
	if (ac == 1)
	{
		while (1)
		{
			// condition pour l'affichage du prompt, que si pas de fork en cours
			write(1, "$>", 2);
			if ((ret = get_next_line(0, &line)) == 1)
			{
				// verify cmd
				// split cmd here and verify validity of case 0
				cmd = split_cmd(line);
				if (*cmd == NULL) // useless ?
					main(ac, av, env);
				ft_putstr("----- MANAGE CMD -----\n\n");
				if (find_cmd_path(path, cmd, env_cpy) != NULL)
				{
					ft_putendl("cmd found in path\n");
					exe_cmd(path, cmd, env_cpy); // fork, wait
					//main(ac, av, env);
				}
				else
				{
					free(line);
					line = NULL;
				}
				ft_putchar('\n'); // test
			}
		}
	}
	else
		ft_putendl_fd("this binary doesn't take any args", 2);
	return (0);
}
