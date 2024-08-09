/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:18:53 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/09 17:14:36 by luiberna         ###   ########.fr       */
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
    char *end_str;

    i = 0;
    if (str[i + 1] == '?')
    {
        end_str = ft_strdup(&str[i + 2]);
        return (end_str);
    }
    while(str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\'' && str[i] != '=')
        i++;
    if (str[i])
    {
        end_str = ft_strdup(&str[i]);
        return (end_str);
    }
    else
        return (NULL);
}

char    *get_env_value(char *str, t_env *env)
{
    int i;
    int name_len;
    char *env_value;

    i = 0;
    name_len = 0;
    while (str[i] != ' ' && str[i] && str[i] != '\"' && str[i] != '\'' && str[i] != '=')
    {
        name_len++;
        i++;
    }
    i = 0;
    while (env->envp[i])
    {
        if (ft_strncmp(str, env->envp[i], name_len) == 0 && env->envp[i][name_len] == '=')
            return (env_value = ft_strdup(&env->envp[i][name_len + 1]), env_value);
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

char    *get_ex_code(t_env *env)
{
    return (ft_itoa(g_ex_code));
}

void free_lines(char *str, char *end_str, char *env_value, char *start_str)
{
    free(str);
    free(end_str);
    free(env_value);
    free(start_str);
}

char    *expand(char *str, t_env *env)
{
    int i;
    char *start_str;
    char *env_value;
    char *end_str;
    char *temp_str;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '$')
        {
           start_str = get_start_str(str);
           if (str[i + 1] == '?')
                env_value = get_ex_code(env);
           else
                env_value = get_env_value(&str[i + 1], env);
           end_str = get_end_str(&str[i]);
           temp_str = create_final_str(start_str, env_value, end_str);
           free_lines(str, end_str, env_value, start_str);
           str = ft_strdup(temp_str);
           free(temp_str);
           i = 0;
        }
    }
    return (str);
}

int verify_next_char(char a)
{
    if (a && ft_isalnum(a) || a == '?' || a == '_')
        return (1);
    return (0);
}

void remove_null_strings(char **cmd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (cmd[i] != NULL)
    {
        if (cmd[i][0] != '\0')
        {
            if (i != j)
                cmd[j] = cmd[i];
            j++;
        } 
        else
            free(cmd[i]);
        i++;
    }
    cmd[j] = NULL;
    if (j == 0)
    {
        cmd[0] = ft_strdup("");
        cmd[1] = NULL;
    }
}

void    expander(t_cmd *cmd, t_env *env)
{
    int i;
    int j;
    char *expanded_str;

    while (cmd)
    {
        i = -1;
        while (cmd->cmd[++i])
        {
            j = -1;
            while (cmd->cmd[i][++j])
            {
                if (cmd->cmd[i][0] == '\'')
                    break;
                if (cmd->cmd[i][j] == '$' && verify_next_char(cmd->cmd[i][j + 1]))
                {
                    expanded_str = expand(cmd->cmd[i], env);
                    cmd->cmd[i] = ft_strdup(expanded_str);
                    free(expanded_str);
                }
            }
        }
        remove_null_strings(cmd->cmd);
        cmd = cmd->next;
    }
}
