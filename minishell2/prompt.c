/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 13:42:55 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/15 17:13:51 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	color(char *color, char *toput)
{
	ft_putchar('\033');
	ft_putstr(color);
	ft_putstr(toput);
}

void		prompt(char **env)
{
	char *home;
	char *user;
	char cwd[100];

	getcwd(cwd, 100);
	user = get_var_content(env, "USER");
	home = get_var_content(env, "HOME");
	color("[36m", "# ");
	if (user)
		ft_putstr(user);
	else
		ft_putstr("incognito");
	color("[39m", " ");
	color("[33m", "");
	if (home && ft_strstr(cwd, home))
	{
		ft_putchar('~');
		ft_putstr(ft_strstr(cwd, home) + ft_strlen(home));
	}
	else
		ft_putstr(cwd);
	ft_strdel(&user);
	ft_strdel(&home);
	color("[39m", " $> ");
}
