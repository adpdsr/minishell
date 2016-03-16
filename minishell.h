/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 12:04:31 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/16 14:35:04 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>

# define RED "[31m"
# define BLUE "[34m"
# define CYAN "[36m"
# define RESET "[39m"
# define GREEN "[32m"
# define YELLOW "[33m"
# define MAGENTA "[35m"

# define LEN(x) ft_tablen(x)

void	execute_cmd(char **cmd, char *cmdp, char **env);
void	free_exit(char **env, char **cmd, char **path);
void	err_not_found(char *cmd, int flag);
void	color(char *color, char *toput);
void	print_env(char **env);
void	prompt(char **env);

char	*get_var_content(char **env, char *var);
char	*find_cmdp(char *cmd, char **path);

int		is_in(char **env, char *cmd);
int		is_builtin(char *cmd);

char	**do_unsetenv(char **cmd, char **env, int flag);
char	**do_builtin(char **cmd, char **env, int flag);
char	**do_setenv(char **cmd, char **env);
char	**do_env(char **cmd, char **env);
char	**do_cd(char **cmd, char **env);

char	**resize_cmd(char **cmd, char **tmp_cmd, int flag);
void	redirect_fork(char **cmd, char **env, int flag);
char	**redirect_setenv(char **cmd, char **env);
char	**ignore_env(char **env, int len);
char	**rm_nl(char **env, int size);

#endif
