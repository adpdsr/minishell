/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:27:17 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/26 19:36:03 by adu-pelo         ###   ########.fr       */
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
#include <unistd.h> // write, chdir
#include <dirent.h> // fork
#include <sys/wait.h> // wait

void	print_tab(char **tab);
int		tab_len(char **tab); // static
char	**cpy_env(char **env);
char	**extract_path(char *env_path);

#endif
