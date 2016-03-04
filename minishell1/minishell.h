/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:27:17 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/28 14:33:11 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"

#include <stdlib.h> // malloc, NULL
#include <stdio.h> // printf
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h> // write, chdir, getcwd
#include <dirent.h> // fork
#include <sys/wait.h> // wait

void	print_tab(char **tab);
int		tab_len(char **tab); // static
char	**cpy_env(char **env);
char	**extract_path(char **env);
char	*extract_var_content(char **env, char *var);

void	print_prompt(char **env);

/* BUILTINS */
char	**do_builtin(char **cmd, char ** path, char **env);
void	print_env(char **tab);

#endif
