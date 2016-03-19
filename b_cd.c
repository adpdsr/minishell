/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 11:59:04 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/19 17:06:06 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_no_arg(char **env)
{
	char		*home;

	home = NULL;
	if (env && *env)
	{
		home = get_var_content(env, "HOME=");
		if (home)
		{
			chdir(home);
			ft_strdel(&home);
		}
		else
			ft_putendl_fd("root path not found in HOME", 2);
	}
	else
		ft_putendl_fd("root path not found in HOME", 2);
}

char		*add_root_path(char **env, char *cmd)
{
	char	*home;
	char	*rest;
	char	*new_cmd;

	new_cmd = NULL;
	home = get_var_content(env, "HOME=");
	if (!cmd[1] || (cmd[1] == '/' && !cmd[2]))
	{
		ft_strdel(&cmd);
		return (home);
	}
	if (home)
	{
		rest = ft_strstr(cmd, "/");
		if (!(new_cmd = (char *)malloc(sizeof(char) *
						(ft_strlen(home) + ft_strlen(cmd) + 1))))
			return (NULL);
		new_cmd = ft_strcpy(new_cmd, home);
		new_cmd = ft_strcat(new_cmd, rest);
		new_cmd = ft_strcat(new_cmd, "/");
		ft_strdel(&home);
		ft_strdel(&cmd);
		return (new_cmd);
	}
	return (NULL);
}

static void	print_error(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	color(RED, s2);
	color(RESET, "\n");
}

static void	try_cd(char *cmd)
{
	struct stat	st;
	DIR			*dir;

	dir = NULL;
	dir = opendir(cmd);
	if (!cmd)
		return ;
	if (stat(cmd, &st))
		print_error("cd: No such file or directory: ", cmd);
	else if (!(S_ISDIR(st.st_mode)))
		print_error("cd: Not a directory: ", cmd);
	else if (access(cmd, X_OK) == -1)
		print_error("cd: Permission denied: ", cmd);
	else
		chdir(cmd);
	if (dir)
		closedir(dir);
}

char		**do_cd(char **cmd, char **env)
{
	int len;

	len = ft_tablen(cmd);
	if (len > 2)
		ft_putendl_fd("cd: wrong number of arguments", 2);
	if (cmd[1] && cmd[1][0] == '~' && cmd[1][1] != '~')
		cmd[1] = add_root_path(env, cmd[1]);
	if (len == 2)
		try_cd(cmd[1]);
	else if (!cmd[1])
		do_no_arg(env);
	else if (len == 2)
		print_error("cd: No such file or directory: ", cmd[1]);
	return (env);
}
