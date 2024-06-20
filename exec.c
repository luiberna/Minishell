/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:04:07 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/20 17:06:19 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    execute(t_cmd *cmd, t_env *env)
{
    // if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
    //     return (ft_cd(cmd, env));
    // else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
    //     return (ft_pwd(cmd, env));
    // else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
    //     return (ft_echo(cmd, env));
    // else if (ft_strncmp(cmd->cmd[0], "export", 8) == 0)
    //     return (ft_export(cmd, env));
    // else if (ft_strncmp(cmd->cmd[0], "unset", 7) == 0)
    //     return (ft_unset(cmd, env));
    // else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
    //     return (ft_env(cmd, env));
    // else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
    //     return (ft_exit(cmd, env));
    // else
        return (execve(cmd->path, cmd->cmd, env->envp));
        
}
