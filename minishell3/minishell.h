/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:04:31 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/12 17:52:33 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>

int		is_in(char **env, char *cmd);

void	prompt(char **env);
void	print_env(char **env);
char	*get_var_content(char **env, char *var);
void	execute_cmd(char **cmd, char *cmdp, char **env);
char	*find_cmdp(char *cmd, char **path);

// BUILTINS
char	**do_cd(char **cmd, char **env);
char	**do_env(char **cmd, char **env);
char	**do_setenv(char **cmd, char **env);
char	**do_unsetenv(char **cmd, char **env);
char	**do_builtin(char **cmd, char **env);

#endif
