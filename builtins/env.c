/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:49 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/08/02 16:49:45 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	builtin_env(t_env *env)
{
	int i;

	i = 0;
	if(!env->envp && !env->envp[0])
		error_msg("Error on env", 1);
	while(env->envp[i])
	{
		if(ft_strchr(env->envp[i], '='))
			printf("%s\n", env->envp[i]);
		i++;
	}
	exit (0);
}