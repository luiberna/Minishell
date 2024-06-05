/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:04:07 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/05 16:18:59 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute(t_cmd *cmd, t_env *env)
{
    int i = 0;
    while (cmd)
    {
        // if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
        //     ft_cd(cmd);
        // else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
        //     ft_pwd(cmd);
        // else if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
        //     ft_echo(cmd);
        // else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
        //     ft_export(cmd);
        // else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
        //     ft_unset(cmd);
        // else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
        //     ft_env(cmd);
        // else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
        //     ft_exit(cmd);
        // else
        //     pipes_exec(cmd, env);
        pipes_exec(cmd, env);
        cmd = cmd->next;
    }
}
