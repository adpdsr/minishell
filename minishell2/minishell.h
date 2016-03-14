/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:04:31 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/14 18:16:35 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>

void	execute_cmd(char **cmd, char *cmdp, char **env);
void	prompt(char **env);
void	print_env(char **env);
char	*get_var_content(char **env, char *var);
char	*find_cmdp(char *cmd, char **path);
int		is_in(char **env, char *cmd);
int		is_builtin(char *cmd);

char	**do_cd(char **cmd, char **env);
char	**do_env(char **cmd, char **env);
char	**do_setenv(char **cmd, char **env);
char	**do_unsetenv(char **cmd, char **env);
char	**do_builtin(char **cmd, char **env);

void	redirect_fork(char **cmd, char **env, int flag);
char	**redirect_setenv(char **cmd, char **env);
char	**rm_nl(char **env, int size);
char	**ignore_env(char **env, int len);
char	**resize_cmd(char **cmd, char **tmp_cmd, int flag);

#endif
