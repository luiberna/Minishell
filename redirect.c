/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:47:09 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/07 17:17:23 by luiberna         ###   ########.fr       */
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
        ft_printf("\033[31mError: Invalid infile\n\3[0m", 2);
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
        ft_printf("\033[31mError: Invalid outfile\n\3[0m", 2);
        close_fds(cmd);
        exit(1);
    }
    dup2(file_out, STDOUT_FILENO);
    close(file_out);
}

void    redirections(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->cmd[i])
    {
        if (ft_strncmp(cmd->cmd[i], "<", 1) == 0)
        {
            redirect_in(cmd, i);
            remove_redirection(cmd, i);
        }
        else if (ft_strncmp(cmd->cmd[i], ">", 1) == 0)
        {
            redirect_out(cmd, i);
            remove_redirection(cmd, i);
        }
        // else if (ft_strncmp(cmd->cmd[i], ">>", 2) == 0)
        //     appending_out(cmd, i);
        // else if (ft_strncmp(cmd->cmd[i], "<<", 2) == 0)
        //     here_doc(cmd, i);
        else
            i++;
    }
}
