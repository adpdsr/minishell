/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:29:00 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/29 11:23:56 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_curr_path(char *path)
{
	int i;
	char *curr;

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

	pwd = NULL;
	ft_putendl("----- PRINT PROMPT -----");
	print_env(env);
	pwd = getcwd(pwd, 20);
	pwd = get_curr_path(pwd);
	user = extract_var_content(env, "USER");
	if (ft_strcmp(pwd, user) == 0)
		pwd = "~";
	ft_putstr(pwd);
	ft_putchar(' ');
	write(1, "$>", 2);
}
