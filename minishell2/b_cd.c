/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 11:59:04 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/15 17:28:39 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_no_arg(char **env)
{
	char		*home;

	home = NULL;
	if (env && *env)
	{
		home = get_var_content(env, "HOME");
		if (home)
		{
			chdir(home);
			ft_strdel(&home);
		}
		else
			ft_putendl("root path not found in HOME");
	}
	else
		ft_putendl("root path not found in HOME");
}

static char	*add_root_path(char **env, char *cmd)
{
	char	*home;
	char	*rest;
	char	*new_cmd;

	new_cmd = NULL;
	home = get_var_content(env, "HOME");
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
	ft_putendl_fd(s2, 2);
}

char		**do_cd(char **cmd, char **env)
{
	DIR			*dir;
	struct stat	st;

	dir = NULL;
	if (cmd[1] && cmd[1][0] == '~')
		cmd[1] = add_root_path(env, cmd[1]);
	if (cmd[1] && (dir = opendir(cmd[1])))
	{
		if (stat(cmd[1], &st))
			print_error("cd: No such file or directory: ", cmd[1]);
		else if (!(S_ISDIR(st.st_mode)))
			print_error("cd: Not a directory: ", cmd[1]);
		else if (access(cmd[1], X_OK) == -1)
			print_error("cd: Permission denied: ", cmd[1]);
		else
			chdir(cmd[1]);
		if (dir)
			closedir(dir);
	}
	else if (!cmd[1])
		do_no_arg(env);
	else
		print_error("cd: No such file or directory: ", cmd[1]);
	return (env);
}
