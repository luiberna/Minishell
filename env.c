/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:33:16 by luiberna          #+#    #+#             */
/*   Updated: 2024/05/07 22:52:09 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *get_env(char **envp)
{
    t_env *env;
    int i;
    int j;

    i = 0;
    j = 0;
    while(envp[j])
        j++;
    env = ft_calloc(sizeof(t_env), sizeof(t_env));
    if(!env)
        return(NULL);
    env->envp = ft_calloc(j + 1, sizeof(char *));
    if(!env->envp)
        return(free(env->envp), NULL);
    while(envp[i])
    {
        env->envp[i] = ft_strdup(envp[i]);
        if(!env->envp[i])
            return(free_list(env->envp), free(env), NULL);
        i++;
    }
    return(env);
}
