/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:24:26 by luiberna          #+#    #+#             */
/*   Updated: 2024/07/05 18:55:33 by luiberna         ###   ########.fr       */
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
    
	if(!cmd)
		return ;
    curr = cmd;
    while (cmd != NULL) //Alterei de curr para cmd porque estava a dar segfault - Artur
    {
        curr = cmd;
        cmd = cmd->next;
        free_list(curr->cmd);
        free(curr->path);
        if (curr->fd[0] != -1)
            close(curr->fd[0]);
        if (curr->fd[1] != -1)
            close(curr->fd[1]);
        free(curr);
    }
}
