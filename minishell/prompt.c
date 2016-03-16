/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 13:42:55 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/16 13:14:50 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		color(char *color, char *toput)
{
	ft_putchar_fd('\033', 2);
	ft_putstr_fd(color, 2);
	ft_putstr_fd(toput, 2);
}

void		prompt(char **env)
{
	char *home;
	char *user;
	char cwd[100];

	getcwd(cwd, 100);
	user = get_var_content(env, "USER");
	home = get_var_content(env, "HOME");
	color(CYAN, "# ");
	if (user)
		ft_putstr(user);
	else
		ft_putstr("incognito");
	color(RESET, " ");
	color(YELLOW, "");
	if (home && ft_strstr(cwd, home))
	{
		ft_putchar('~');
		ft_putstr(ft_strstr(cwd, home) + ft_strlen(home));
	}
	else
		ft_putstr(cwd);
	ft_strdel(&user);
	ft_strdel(&home);
	color(RESET, " $> ");
}
