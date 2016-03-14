/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 13:42:55 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/14 18:56:03 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **env)
{
	char *home;
	char *user;
	char cwd[100];

	if (env && *env)
	{
		ft_putendl("in prompt");
		getcwd(cwd, 100);
		ft_putendl("prompt.1");
		user = get_var_content(env, "USER");
		ft_putendl("prompt.2");
		home = get_var_content(env, "HOME");
		ft_putendl("prompt.3");
		if (user)
			ft_putstr(user);
		else
			ft_putstr("incognito");
		ft_putendl("prompt.4");
		ft_putchar(' ');
		if (home && ft_strstr(cwd, home))
		{
			ft_putchar('~');
			ft_putstr(ft_strstr(cwd, home) + ft_strlen(home));
		}
		else
			ft_putstr(cwd);
		ft_strdel(&user);
		ft_strdel(&home);
		ft_putchar(' ');
	}
	write(1, "$>", 3);
}
