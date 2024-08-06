/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:51 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/08/06 14:59:32 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int		unset_exists(t_env *env, char *cmd)
{
	int i;

	i = 0;
	while(env->envp[i])
	{
		if(ft_strncmp(cmd, env->envp[i], ft_strlen(cmd)) == 0)
			return 1;
		i++;
	}
	return 0;
}

void	unset(t_env *env, char *cmd)
{
	int i;
	int eq;

	i = 0;
	if(env->envp && env->envp[i])
	{
		if(!unset_exists(env, cmd))
			return ;
		eq = find_eq(env->envp[i]);
		while(env->envp[i] && ft_strncmp(cmd, env->envp[i], eq))
		{
			i++;
			eq = find_eq(env->envp[i]);
		}
		free(env->envp[i]);
		env->envp[i] = env->envp[i + 1];
		i++;
		while(env->envp[i])
		{
			env->envp[i] = env->envp[i + 1];
			i++;
		}
		env->envp[i] = NULL;
	}
}

void	builtin_unset(t_env *env, t_cmd *cmd)
{
	int i;

	if(!cmd->cmd[1])
	{
		env->ex_code = 0;
		return ;
	}
	else
	{
		i = 1;
		while(cmd->cmd && cmd->cmd[i])
		{
			if(error_handler(cmd->cmd[i]))
			{
				env->ex_code = 1;
				return ;
			}
			unset(env, cmd->cmd[i]);
			i++;
		}
	}
}
