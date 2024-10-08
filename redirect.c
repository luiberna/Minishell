/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:47:09 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/09 19:58:35 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Anda com os elementos para a esquerda e remove a redirection e o file*/
void remove_redirection(t_cmd *cmd, int i)
{
    if(cmd->cmd[i + 2])
    {
        while (cmd->cmd[i + 2])
        {
            cmd->cmd[i] = ft_strdup(cmd->cmd[i + 2]);
            free(cmd->cmd[i + 2]);
            i++;
        }
        cmd->cmd[i] = NULL;
        cmd->cmd[i + 1] = NULL;
    }
    else
    {
        free(cmd->cmd[i]);
        free(cmd->cmd[i + 1]);
        cmd->cmd[i] = NULL;
        cmd->cmd[i + 1] = NULL;   
    }
}

void    redirect_in(t_cmd *cmd, int i)
{
    int file_in;

    if (!cmd->cmd[i + 1] || ft_strncmp(cmd->cmd[i + 1], ">", 1) == 0 || ft_strncmp(cmd->cmd[i + 1], "<", 1) == 0)
        error_msg("Parse error near '<'", 2);
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
    
    if (!cmd->cmd[i + 1] || ft_strncmp(cmd->cmd[i + 1], ">", 1) == 0 || ft_strncmp(cmd->cmd[i + 1], "<", 1) == 0)
        error_msg("Parse error near '>'", 2);
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

    if (!cmd->cmd[i + 1] || ft_strncmp(cmd->cmd[i + 1], ">", 1) == 0 || ft_strncmp(cmd->cmd[i + 1], "<", 1) == 0)
        error_msg("Parse error near '>>'", 2);
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

void	signals_here_doc(int sign)
{
	if (sign == SIGINT)
		exit(130);
}

void here_doc(t_cmd *cmd, int i, int write_fd) 
{
    char *line;

    if (!cmd->cmd[i + 1] || ft_strncmp(cmd->cmd[i + 1], ">", 1) == 0 || ft_strncmp(cmd->cmd[i + 1], "<", 1) == 0)
        error_msg("Parse error near '<<'", 2);
    while (1)
    {
        signal(SIGINT, signals_here_doc);
        line = readline("> ");
        if (line == NULL || strcmp(line, cmd->cmd[i + 1]) == 0)
        {
            free(cmd->cmd[i]);
            free(cmd->cmd[i + 1]);
            free(line);
            break;
        }
        write(write_fd, line, strlen(line));
        write(write_fd, "\n", 1);
        free(line);
    }
}

int     check_here(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->cmd[i])
    {
        if (strncmp(cmd->cmd[i], "<<", 2) == 0)
            return (1);
        else
            i++;
    }
    return (0);
}

void redirect_here(t_cmd *cmd)
{
    int i;
    int pipe_fd[2];
    
    i = 0;
    if (check_here(cmd))
    {
        if (pipe(pipe_fd) == -1)
            error_msg("Pipe creation failed", 1);
        while (cmd->cmd[i])
        {
            if (strncmp(cmd->cmd[i], "<<", 2) == 0)
            {
                here_doc(cmd, i, pipe_fd[1]);
                remove_redirection(cmd, i);
            }
            else
                i++;
        }
        close(pipe_fd[1]); // Fecha a write da pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect da read da pipe para o STDIN
        close(pipe_fd[0]); // Fecha a read da pipe
    }
}

void    redirections(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->cmd[i])
    {
        if(ft_strncmp(cmd->cmd[i], "<", 2) == 0)
        {
            redirect_in(cmd, i);
            remove_redirection(cmd, i);
        }
        else if (ft_strncmp(cmd->cmd[i], ">>", 2) == 0)
        {
            appending_out(cmd, i);
            remove_redirection(cmd, i);
        }
        else if (ft_strncmp(cmd->cmd[i], ">", 2) == 0)
        {
            redirect_out(cmd, i);
            remove_redirection(cmd, i);
        }
        else
            i++;
    }
}
