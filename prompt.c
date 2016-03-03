/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:29:00 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/03 16:33:12 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_curr_path(char *path)
{
	int		i;
	char	*curr;

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

void	print_prompt(char **env)
{
	char *pwd;
	char *home;
	char *user;

	if (env)
	{
		printf("debug1\n");
		pwd = NULL;
		pwd = getcwd(pwd, 20);
		printf("debug2\n");
		pwd = get_curr_path(pwd);
		printf("debug3\n");
		user = extract_var_content(env, "USER");
		printf("debug4\n");
		if (pwd && user && ft_strcmp(pwd, user) == 0)
			pwd = "~";
		if (pwd)
			ft_putstr(pwd);
		ft_putchar(' ');
	}
	write(1, "$>", 2);
}
