/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:18:53 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/24 18:31:42 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin_free(char *s1, char *s2)
{
    char *result = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return result;
}

char *get_env_value(char *name, t_env *env)
{
    int i;
    int name_len;

    i = 0;
    name_len = ft_strlen(name);
    while (env->envp[i])
    {
        if (ft_strncmp(name, env->envp[i], name_len) == 0 && env->envp[i][name_len] == '=')
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

char    *create_final_str(char *start_str, char *env_value, char *end_str)
{
    char *temp_str1;
    char *temp_str2;

    if (start_str)
    {
        if (env_value)
            temp_str1 = ft_strjoin_free(start_str, env_value);
        else
            temp_str1 = ft_strjoin_free(start_str, "");
        free (start_str);
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
        temp_str2 = ft_strjoin_free(temp_str1, end_str);
        free(end_str);
        free(temp_str1);
    }
    else
        temp_str2 = temp_str1;
    return (temp_str2);
}

char    *expand_with_quotes(char *str, t_env *env)
{
    int i;
    char *start_str;
    char *end_str;
    char *env_value;
    char *temp_str;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
           start_str = get_start_str(str);
           env_value = get_env_value(&str[i + 1], env);
           while (str[i] != ' ' || str[i] != '\0')
                i++;
           if (str[i] == '\0')
                end_str = NULL;
           else
                end_str = ft_strdup(&str[i]);
           temp_str = create_final_str(start_str, env_value, end_str);
           free(end_str);
           free(str);
           str = ft_strdup(temp_str);
           i = 0;
        }
        i++;
    }
    return (str); 
}

void    expander(t_cmd *cmd, t_env *env)
{
    int i;
    char *env_value;
    char *expanded_str;

    while (cmd)
    {
        i = 0;
        while (cmd->cmd[i])
        {
            if (cmd->cmd[i][0] == '$')
            {
                env_value = get_env_value(cmd->cmd[i] + 1, env);
                free(cmd->cmd[i]);
                if (env_value)
                    cmd->cmd[i] = ft_strdup(env_value);
                else
                    cmd->cmd[i] = ft_strdup("");
            }
            else if (cmd->cmd[i][0] == '\"')
            {
                expanded_str = expand_with_quotes(cmd->cmd[i], env);
                free(cmd->cmd[i]);
                cmd->cmd[i] = ft_strdup(expanded_str);
                free(expanded_str);
            }
            i++;
        }
        cmd = cmd->next;
    }
}
