/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:16:52 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/07 20:45:52 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_fds(t_cmd *cmd)
{
    t_cmd *curr;
    int nb;

    nb = (cmd->nb_cmds * 2);
    curr = cmd;
    while (curr)
    {
        if (curr->fd[0] > 2)
            close(curr->fd[0]);
        if (curr->fd[1] > 2)
            close(curr->fd[1]);
        curr = curr->next;
    }
    while (nb > 2)
    {
        close(nb);
        nb--;
    }
}

void error_msg(char *str, int ex_nb)
{
    perror(str);
    exit(ex_nb);
}

void execve_aux(t_cmd *cmd, t_env *env)
{
    char *path;

    path = get_path(cmd->cmd[0], env->envp);
    if (!cmd->cmd || !cmd->cmd[0])
        free(cmd->path);
    if (cmd->cmd[0][0] == '/' && (access(cmd->cmd[0], F_OK) == 0))
    {
        free(cmd->path);
        cmd->path = ft_strdup(cmd->cmd[0]);
    }
    if (access(cmd->cmd[0], X_OK) != 0 && path == NULL)
    {
        free(path);
        error_msg("Error on execve", 127);
    }
    if (execute(cmd, env) == -1)
    {
        free(path);
        error_msg("Error on execve", 127);
    }
    free(path);
    exit(1);
}

void command_exec(t_cmd *cmd, t_env *env)
{
    pid_t pid;
    
    pid = fork();
    if (pid == 0) //Child process
    {
        redirect_here(cmd);
        if (cmd->fd[0] > 2)
        {
            dup2(cmd->fd[0], STDIN_FILENO); //Redireciona o input do comando anterior
            close(cmd->fd[0]); //Fecha o fd original
        }
        if (cmd->fd[1] > 2)
        {
            dup2(cmd->fd[1], STDOUT_FILENO); //Redireciona o output para o proximo comando
            close(cmd->fd[1]); //Fecha o fd original
        }
        redirections(cmd);
        close_fds(cmd); //Fecha todos os fds na child
        execve_aux(cmd, env); //Executa o comando na child
        exit(0);
    }
    else if (pid < 0)
        error_msg("Erro on fork", 1);
}

void    setup_pipes(t_cmd *cmd)
{
    t_cmd *curr;
    int pipe_fd[2];

    curr = cmd;
    while (curr)
    {
        if (curr->next)
        {
            if (pipe(pipe_fd) == -1)
                error_msg("Error on pipe", 1);
            curr->fd[1] = pipe_fd[1];
            curr->next->fd[0] = pipe_fd[0];
        }
        curr = curr->next;
    }
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
        return 1;
    else if (ft_strncmp(cmd, "export", 8) == 0)
        return 1;
    else if (ft_strncmp(cmd, "unset", 7) == 0)
        return 1;
    else if (ft_strncmp(cmd, "exit", 5) == 0)
        return 1;
	return 0;
}

void pipes_exec(t_cmd *cmd, t_env *env)
{
    t_cmd *curr;
    int status;

    setup_pipes(cmd);
    curr = cmd;
    while (curr)
    {
        if (is_builtin(curr->cmd[0])) //Adicionado caso seja builtin - Artur - Atualizei para ser else if
			execute(curr, env);
        else if (curr->cmd && curr->cmd[0])
            command_exec(curr, env);
        curr = curr->next;
    }
    close_fds(cmd); //Fecha todos os fds no parent;
    curr = cmd;
    while (curr)
    {
        if(is_builtin(curr->cmd[0]))
			;
        else if (waitpid(-1, &status, 0) == -1) //O primeiro -1 define que o wait deve esperar por qualquer child process
            error_msg("Error on waitpid", 1);
        if (WIFEXITED(status))
            env->ex_code = WEXITSTATUS(status);
        curr = curr->next;
    }
}
