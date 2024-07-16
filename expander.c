/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:18:53 by luiberna          #+#    #+#             */
/*   Updated: 2024/07/15 19:03:42 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *create_final_str(char *start_str, char *env_value, char *end_str)
{
    char *temp_str1;
    char *temp_str2;

    if (start_str)
    {
        if (env_value)
            temp_str1 = ft_strjoin(start_str, env_value);
        else
            temp_str1 = ft_strjoin(start_str, "");
    }
    else
    {
        if (env_value)
            temp_str1 = ft_strdup(env_value);
        else
            temp_str1 = ft_strdup("");
    }
    if (end_str)
    {
        temp_str2 = ft_strjoin(temp_str1, end_str);
        free(temp_str1);
    }
    else
        temp_str2 = temp_str1;
    return (temp_str2);
}

char    *get_end_str(char *str)
{
    int i;

    i = 0;
    while(str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
        i++;
    if (str[i])
        return (&str[i]);
    else
        return (NULL);
}

char    *get_env_value(char *str, t_env *env)
{
    int i;
    int name_len;

    i = 0;
    name_len = 0;
    while (str[i] != ' ' && str[i] && str[i] != '\"' && str[i] != '\'')
    {
        name_len++;
        i++;
    }
    i = 0;
    while (env->envp[i])
    {
        if (ft_strncmp(str, env->envp[i], name_len) == 0 && env->envp[i][name_len] == '=')
            return (&env->envp[i][name_len + 1]);
        i++;
    }
    return (NULL);
}

char    *get_start_str(char *str)
{
    int i;
    char *temp_str;

    i = 0;
    while (str[i] && str[i] != '$')
        i++;
    if (i == 0)
        return (NULL);
    temp_str = ft_calloc(i + 1, sizeof(char));
    if (!temp_str)
        return (NULL);
    i = 0;
    while (str[i] != '$')
    {
        temp_str[i] = str[i];
        i++;
    }
    temp_str[i] = '\0';
    return (temp_str);
}

char    *expand(char *str, t_env *env)
{
    int i;
    char *start_str;
    char *env_value;
    char *end_str;
    char *temp_str;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
           start_str = get_start_str(str);
           env_value = get_env_value(&str[i + 1], env);
           end_str = get_end_str(&str[i]);
           temp_str = create_final_str(start_str, env_value, end_str);
           str = temp_str;
           i = 0;
        }
        i++;
    }
    return (str); 
}

void    expander(t_cmd *cmd, t_env *env)
{
    int i;
    int j;
    char *expanded_str;

    while (cmd)
    {
        i = 0;
        while (cmd->cmd[i])
        {
            j = -1;
            while (cmd->cmd[i][++j])
            {
                if (cmd->cmd[i][0] == '\'')
                    break;
                if (cmd->cmd[i][j] == '$')
                {
                    expanded_str = expand(cmd->cmd[i], env);
                    free(cmd->cmd[i]);
                    cmd->cmd[i] = ft_strdup(expanded_str);
                }
            }
            i++;
        }
        cmd = cmd->next;
    }
}
