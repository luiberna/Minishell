/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:35:24 by luiberna          #+#    #+#             */
/*   Updated: 2024/07/15 19:09:25 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_quotes(t_cmd *cmd)
{
    int i;
    int j;
    int k;
    char *new_str;
    char quote;

    i = 0;
    while (cmd)
    {
        while (cmd->cmd[i])
        {
            new_str = (char *)malloc(ft_strlen(cmd->cmd[i]) + 1);
            j = 0;
            k = 0;
            while (cmd->cmd[i][j])
            {
                if (cmd->cmd[i][j] == '\'' || cmd->cmd[i][j] == '\"')
                {
                    quote = cmd->cmd[i][j];
                    j++;
                    while (cmd->cmd[i][j] && cmd->cmd[i][j] != quote)
                        new_str[k++] = cmd->cmd[i][j++];
                    if (cmd->cmd[i][j] == quote)
                        j++;
                }
                else
                    new_str[k++] = cmd->cmd[i][j++];
            }
            new_str[k] = '\0';
            //free(cmd->cmd[i]);//<---- estava a eliminar o path
            cmd->cmd[i] = new_str;
            i++;
        }
        cmd = cmd->next;
    }
}

/*Divide o input por comandos e respetivos argumentos substituindo as pipes ('|') por um caracter inexistente
'\4' e separando os comandos dos argumentos substituindo os espacos por '\3'.
Adiciona um espaco entre as redirects da seguinte forma: (\3>>\3) de forma a albergar todos os casos.*/
t_cmd   *lexer_args(char *input, char **envp)
{
    int flag;
    int flag2;
    int i;
    int j;
    char *lx_input;

    i = 0;
    j = 0;
    flag = 1;
    flag2 = 1;
    lx_input = ft_calloc(sizeof(char), (ft_strlen(input) * 3));
    while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
        i++;
    while (input[i])
    {
        if (input[i] == ' ' && flag == 1 && flag2 == 1)
            lx_input[j++] = '\3';
        else if (input[i] == '|' && flag == 1 && flag2 == 1)
            lx_input[j++] = '\4';
        else if ((ft_strncmp(input + i, ">>", 2) == 0 || ft_strncmp(input + i, "<<", 2) == 0) && flag == 1 && flag2 == 1)
        {
            lx_input[j++] = '\3';
            lx_input[j++] = input[i++];
            lx_input[j++] = input[i];
            lx_input[j++] = '\3';
        }
        else if ((input[i] == '>' || input[i] == '<') && flag == 1 && flag2 == 1)
        {
            lx_input[j++] = '\3';
            lx_input[j++] = input[i];
            lx_input[j++] = '\3';
        }
        else if (input[i] == '"')
        {
            flag *= -1;
            lx_input[j++] = input[i];
        }
        else if (input[i] == '\'')
        {
            flag2 *= -1;
            lx_input[j++] = input[i];
        }
        else if (flag == 1 && flag2 == 1)
            lx_input[j++] = input[i];
        else
            lx_input[j++] = input[i];
        i++;
    }
    lx_input[j] = '\0';
    return (init_cmd(lx_input, envp));
}
