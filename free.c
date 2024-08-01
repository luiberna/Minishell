/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:26 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/01 18:56:06 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_list(char **list)
{
    int i;
    
    i = 0;
    while (list[i])
    {
        free(list[i]);
        i++;
    }
    free(list);
}

void    free_cmd(t_cmd *cmd)
{
    t_cmd *curr;

    if (!cmd)
        return ;
    curr = cmd;
    while (cmd && cmd != NULL)
    {
        curr = cmd;
        cmd = cmd->next;
        if (curr->cmd)
            free_list(curr->cmd);
        if (curr->path && curr->path != curr->cmd[0]) //Make sure not to double free
            free(curr->path);
        if (curr->fd[0] != -1)
            close(curr->fd[0]);
        if (curr->fd[1] != -1)
            close(curr->fd[1]);
        free(curr);
    }
}
