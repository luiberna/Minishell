/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:04:07 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/05 13:52:25 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    execute(t_cmd *cmd, t_env *env)
{
    if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
        builtin_cd(env, cmd);
    else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
        builtin_pwd(cmd);
    else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
        builtin_echo(cmd->cmd);
    else if (ft_strncmp(cmd->cmd[0], "export", 8) == 0)
        builtin_export(env, cmd);
    else if (ft_strncmp(cmd->cmd[0], "unset", 7) == 0)
        builtin_unset(env, cmd);
    else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
        builtin_env(env);
    else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
        builtin_exit(cmd, cmd->cmd, env);
    else
        return (execve(cmd->path, cmd->cmd, env->envp));
	return (1);
}
