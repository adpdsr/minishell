/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:29:00 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/25 18:14:54 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <dirent.h>

#include "get_next_line.h"
#include "../ft_ls/libft/libft.h" // test

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

int		is_valid_cmd(char **path, char *cmd) // ret 1 if cmd found in **path else 0
{
	DIR 			*dir;
	struct dirent 	*ret;

	if (cmd)
	{
		if (ft_strcmp(cmd, "exit") == 0)
			exit(0);
		while (*path && path)
		{
			if ((dir = opendir(*path)))
			{
				while ((ret = readdir(dir)))
				{
					if (ft_strcmp(ret->d_name, cmd) == 0)
						return (1);
				}
			}
			path++;
		}
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	int 	ret;
	char 	**path;
	char	*line;
	char	**env_cpy;

	ret = 0;
	line = NULL;

	/* copie du tableau char **env ==> char **env_cpy */
	print_tab(env); // test
	ft_putstr("----- CPY OF ORIGINAL ENV TAB -----\n\n");
	env_cpy = cpy_env(env);
	print_tab(env_cpy); // test

	/* extraction des path contenus dans PATH ==> char **path */
	ft_putstr("----- CPY OF PATH CONTAINED IN PATH ENV_VAR PATH -----\n\n");
	while (*env_cpy && env_cpy)
	{
		if ((path = extract_path(ft_strstr(*env_cpy, "PATH"))) != NULL)
			break ;
		else
			env_cpy += 1;
	}
	print_tab(path); // test

	// parcourir les path de la var PATH dans l'ordre pour trouver la commande

	if (ac == 1)
	{
		while (1)
		{
			write(1, "$>", 2);
			if ((ret = get_next_line(0, &line)) > 0)
			{
				// verify cmd
				if (is_valid_cmd(path, line) == 1)
				{
					// exe cmd -> fork()
					ft_putstr(line);
					ft_putendl(" is valid but no action defined for it");
				}
				else
				{
					ft_putstr("minishell: command not found: ");
					ft_putendl(line);
				}
				ft_putchar('\n'); // test
			}
		}
	}
	else
		ft_putendl_fd("this binary doesn't take any args", 2);
	return (0);
}
