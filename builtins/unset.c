/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:51 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/07/04 18:50:51 by ajorge-p         ###   ########.fr       */
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
			exit (1);
		eq = find_eq(env->envp[i]);
		while(env->envp[i] && ft_strncmp(cmd, env->envp[i], eq))
		{
			i++;
			eq = find_eq(env->envp[i]);
		}
		printf("Valor de I = %d\n", i);
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
		exit (1);
	else
	{
		i = 1;
		while(cmd->cmd && cmd->cmd[i])
		{
			if(error_handler(cmd->cmd[i]))
				export_error(cmd, i, cmd->cmd);
			unset(env, cmd->cmd[i]);
			i++;
		}
	}
	exit(0);
}