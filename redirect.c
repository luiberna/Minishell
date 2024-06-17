/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:47:09 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/17 23:39:39 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_redirection(t_cmd *cmd, int i)
{
    //Anda com os elementos para a esquerda e remove a redirection e o file
    while (cmd->cmd[i + 2])
    {
        cmd->cmd[i] = cmd->cmd[i + 2];
        i++;
    }
    cmd->cmd[i] = NULL;
    cmd->cmd[i + 1] = NULL;
}

void    redirect_in(t_cmd *cmd, int i)
{
    int file_in;

    file_in = open(cmd->cmd[i + 1], O_RDONLY, 0777);
    if (file_in == -1)
    {
        write(2, "Error: Invalid infile\n", 23);
        close_fds(cmd);
        exit(1);
    }
    dup2(file_in, STDIN_FILENO);
    close(file_in);
}

void    redirect_out(t_cmd *cmd, int i)
{
    int file_out;
    
    file_out = open(cmd->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (file_out == -1)
    {
        write(2, "Error: Invalid outfile\n", 24);
        close_fds(cmd);
        exit(1);
    }
    dup2(file_out, STDOUT_FILENO);
    close(file_out);
}

void appending_out(t_cmd *cmd, int i)
{
    int file_out;

    file_out = open(cmd->cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (file_out == -1)
    {
        write(2, "Error: Invalid outfile\n", 24);
        close_fds(cmd);
        exit(1);
    }
    dup2(file_out, STDOUT_FILENO);
    close(file_out);
}

void here_doc(t_cmd *cmd, int i)
{
    int pipe_fd[2];
    char *line;

    if (pipe(pipe_fd) == -1)
    {
        write(2, "Error: Pipe creation failed\n", 28);
        close_fds(cmd);
        exit(1);
    }
    if (!cmd->cmd[i + 1])
    {
        write(2, "Error: Reading input failed\n", 28);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close_fds(cmd);
        exit(1);
    }
    while (1)
    {
        line = readline("> ");
        if (ft_strncmp(line, cmd->cmd[i + 1], ft_strlen(cmd->cmd[i + 1])) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
}

void    redirect_here(t_cmd *cmd)
{
    int i;
    
    i = 0;
    while (cmd->cmd[i])
    {
        if (ft_strncmp(cmd->cmd[i], "<<", 2) == 0)
        {
            here_doc(cmd, i);
            remove_redirection(cmd, i);
        }
        else
            i++;
    }
}

void    redirections(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->cmd[i])
    {
        if(ft_strncmp(cmd->cmd[i], "<", 1) == 0)
        {
            redirect_in(cmd, i);
            remove_redirection(cmd, i);
        }
        else if (ft_strncmp(cmd->cmd[i], ">>", 2) == 0)
        {
            appending_out(cmd, i);
            remove_redirection(cmd, i);
        }
        else if (ft_strncmp(cmd->cmd[i], ">", 1) == 0)
        {
            redirect_out(cmd, i);
            remove_redirection(cmd, i);
        }
        else
            i++;
    }
}
