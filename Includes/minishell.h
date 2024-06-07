/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:58:43 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/07 16:54:43 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
    char **envp;
    struct s_env *next;
    struct s_env *prev;
}               t_env;

typedef struct s_cmd
{
    char **cmd;
    char *path;
    int fd[2];
    int fd_redirect[2];
    pid_t pid;
    int nb_cmds;
    struct s_cmd *next;
    struct s_cmd *prev;
}               t_cmd;

//env
t_env   *get_env(char **envp);

//exec
void    execute(t_cmd *cmd, t_env *env);

//free
void    free_list(char **list);
void    free_cmd(t_cmd *cmd);

//init
char	*get_path(char *cmd, char **envp);
t_cmd   *create_cmd(char *sep_cmd, t_cmd *prev_cmd, int i, char **envp);
t_cmd   *init_cmd(char *input, char **envp);

//parse
int     arglen(char *input);
t_cmd   *lexer_args(char *input, char **envp);

//pipes
void	close_fds(t_cmd *cmd);
void	error_msg(char *str);
void    execve_aux(t_cmd *cmd, t_env *env);
void    command_exec(t_cmd *cmd, t_env *env);
void    pipes_exec(t_cmd *cmd, t_env *env);
void    setup_pipes(t_cmd *cmd);

//redirect
void    remove_redirection(t_cmd *cmd, int i);
void    redirect_in(t_cmd *cmd, int i);
void    redirections(t_cmd *cmd);

#endif