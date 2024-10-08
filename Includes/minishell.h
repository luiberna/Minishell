/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:58:43 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/09 17:14:13 by luiberna         ###   ########.fr       */
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
}               t_env;

typedef struct s_cmd
{
    char **cmd;
    char *path;
    int fd[2];
    pid_t pid;
    int nb_cmds;
    struct s_cmd *next;
}               t_cmd;

typedef enum e_err_msg
{
	CMD_NOT_FOUND,
	NO_FILE,
	PERM_DENIED,
	AMBIGOUS_MSG,
	TOO_MANY_ARGS,
	NUM_REQUIRED,
}           t_err_msg;

typedef struct s_error
{
	t_err_msg type;
	char *msg;
}       t_error;

extern int g_ex_code;

//signals
void	signals_default(t_env *env);
void	signals_default_child(void);
void	handle_sign(int sign);
void	handle_quit(int sign);

//builtins
void    var_exists(char *var, char *value, t_env *env);
void	builtin_cd(t_env *env, t_cmd *cmd);
void	builtin_unset(t_env *env, t_cmd *cmd);
void	builtin_export(t_env *env, t_cmd *cmd);
void	builtin_exit(t_cmd *ms, char **cmd, t_env *env);
void	builtin_env(t_env *env);
void	builtin_pwd(t_cmd *cmd);
void	builtin_echo(char **cmd);

//env
t_env   *get_env(char **envp);

//exec
int    execute(t_cmd *cmd, t_env *env);

//expander
void    expander(t_cmd *cmd, t_env *env);

//free
void    free_list(char **list);
void    free_cmd(t_cmd *cmd);

//init
char	*get_path(char *cmd, char **envp);
t_cmd   *create_cmd(char *sep_cmd, int i, char **envp);
t_cmd   *init_cmd(char *input, t_env *env);

//parse
void    remove_quotes(t_cmd *cmd); //<------Novo
t_cmd   *lexer_args(char *input, t_env *env);

//pipes
void	close_fds(t_cmd *cmd);
void	error_msg(char *str, int ex_nb);
void    execve_aux(t_cmd *cmd, t_env *env);
void    command_exec(t_cmd *cmd, t_env *env);
void    pipes_exec(t_cmd *cmd, t_env *env);
void    setup_pipes(t_cmd *cmd);

//redirect
void    remove_redirection(t_cmd *cmd, int i);
void    redirect_in(t_cmd *cmd, int i);
void    redirect_out(t_cmd *cmd, int i);
void    appending_out(t_cmd *cmd, int i);
void    here_doc(t_cmd *cmd, int i, int write_fd); 
void    redirect_here(t_cmd *cmd);
void    redirections(t_cmd *cmd);

//Utils
int     ft_strcmp(char *s1, char *s2);
int     find_eq(char *str);
void	export_error(t_cmd *cmd, int i, char **str, t_env *env);
int     error_handler(char *cmd);

#endif