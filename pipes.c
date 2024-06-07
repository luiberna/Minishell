/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:16:52 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/07 17:12:17 by luiberna         ###   ########.fr       */
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
        if (curr->fd_redirect[0] > 2)
            close(curr->fd_redirect[0]);
        if (curr->fd_redirect[1] > 2)
            close(curr->fd_redirect[1]);
        curr = curr->next;
    }
    while (nb > 3)/*Nao estava a conseguir fechar
    todos os fds entao arranjei esta forma rudimentar*/
    {
        close(nb);
        nb--;
    }
}

void error_msg(char *str)
{
    perror(str);
    exit(1);
}

void execve_aux(t_cmd *cmd, t_env *env)
{
    if (!cmd->cmd || !cmd->cmd[0])
        free(cmd->path);
    if (execve(cmd->path, cmd->cmd, env->envp) == -1)
        error_msg("Error on execve");
    exit(1);
}

void command_exec(t_cmd *cmd, t_env *env)
{
    pid_t pid;
    
    pid = fork();
    if (pid == 0) //Child process
    {
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
        error_msg("Erro no fork");
}

void    setup_pipes(t_cmd *cmd)
{
    t_cmd *curr;
    int pipefd[2];

    curr = cmd;
    while (curr)
    {
        if (curr->next)
        {
            if (pipe(pipefd) == -1)
                error_msg("Error on pipe");
            curr->fd[1] = pipefd[1];
            curr->next->fd[0] = pipefd[0];
        }
        curr = curr->next;
    }
}

void pipes_exec(t_cmd *cmd, t_env *env)
{
    t_cmd *curr;

    setup_pipes(cmd);
    curr = cmd;
    while (curr)
    {
        if (curr->cmd && curr->cmd[0])
            command_exec(curr, env);
        curr = curr->next;
    }
    close_fds(cmd); //Fecha todos os fds no parent;
    curr = cmd;
    while (curr)
    {
        if (waitpid(-1, NULL, 0) == -1) //O primeiro -1 define que o wait deve esperar por qualquer child process
            error_msg("Error on waitpid");
        curr = curr->next;
    }
}
