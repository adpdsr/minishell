//
// HEADER
//

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


void	prompt(char **env);
void	print_env(char **env);
char	*get_var_content(char **env, char *var);
int	is_in(char **env, char *cmd);
void	execute_cmd(char **cmd, char *cmdp, char **env);

// BUILTINS
char	**do_cd(char **cmd, char **env);
char	**do_env(char **cmd, char **env);
char	**do_setenv(char **cmd, char **env);
char	**do_unsetenv(char **cmd, char **env);
char	**do_builtin(char **cmd, char **path, char **env);

#endif
