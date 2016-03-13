/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 13:42:55 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/12 18:30:46 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **env)
{
	char *home;
	char *user;
	char cwd[100];

	getcwd(cwd, 100);
	user = get_var_content(env, "USER");
	home = get_var_content(env, "HOME");
	if (user)
		ft_putstr(user);
	else
		ft_putstr("incognito");
	ft_putchar(' ');
	if (home && ft_strstr(cwd, home))
	{
		ft_putchar('~');
		ft_putstr(ft_strstr(cwd, home) + ft_strlen(home));
	}
	else
		ft_putstr(cwd);
	write(1, " $>", 3);
	ft_strdel(&user);
	ft_strdel(&home);
}
