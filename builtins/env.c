/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:49 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/07/04 18:49:58 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	builtin_env(t_env *env)
{
	int i;

	i = 0;
	if(!env->envp && !env->envp[0])
		error_msg("Error on env");
	while(env->envp[i])
	{
		if(ft_strchr(env->envp[i], '='))
			printf("%s\n", env->envp[i]);
		i++;
	}
	exit (0);
}