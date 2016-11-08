/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 13:42:55 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/21 16:24:40 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		color(char *color, char *toput)
{
	ft_putchar_fd('\033', 2);
	ft_putstr_fd(color, 2);
	ft_putstr_fd(toput, 2);
}

static void	put_home(char *cwd, char *home)
{
	ft_putchar('~');
	ft_putstr(ft_strstr(cwd, home) + ft_strlen(home));
}

static char	**refresh_content(char **env, char *s, char *content)
{
	int		i;
	char	*tmp;

	i = 0;
	if (env && *env)
	{
		i = -1;
		while (env[++i])
			if (!ft_strncmp(env[i], s, ft_strlen(s)) && content)
			{
				tmp = ft_strdup(env[i]);
				tmp = ft_strjoin(s, content);
				env[i] = tmp;
				return (env);
			}
		return (env);
	}
	return (NULL);
}

static void	put_prompt(char *user, char *home, char *cwd)
{
	color(CYAN, "# ");
	if (user)
		ft_putstr(user);
	else
		ft_putstr("incognito");
	color(RESET, " ");
	color(YELLOW, "");
	if (home && ft_strstr(cwd, home))
		put_home(cwd, home);
	else if (cwd[0])
		ft_putstr(cwd);
	else
		color(RED, "nowhere");
	ft_strdel(&user);
	ft_strdel(&home);
	color(RESET, " $> ");
}

void		prompt(char **env, int nb)
{
	char *ref_pwd;
	char *home;
	char *user;
	char cwd[150];

	ref_pwd = NULL;
	if (nb)
		ref_pwd = get_var_content(env, "PWD=");
	else
		ref_pwd = ft_strnew(150);
	ft_bzero(cwd, 150);
	getcwd(cwd, 150);
	env = refresh_content(env, "PWD=", cwd);
	user = get_var_content(env, "USER=");
	home = get_var_content(env, "HOME=");
	put_prompt(user, home, cwd);
	if (nb)
		env = refresh_content(env, "OLDPWD=", ref_pwd);
}
