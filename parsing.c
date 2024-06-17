/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:35:24 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/14 16:48:59 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Aumenta a lenght consoante a existencia de redirections sendo que antes e apos a redirection precisamos de um indicador
'\3' para indicar a existencia de um novo argumento para prevenir ">>>", ">teste" ou "echo "hello">o" separando "\3>>\3>" "\3>\3teste"
respetivamente*/
int     arglen(char *input)
{
    int i;
    int len;
    
    i = 0;
    len = 0;
    while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
        i++;
    while (input[i])
    {
        if (input[i] == '>' && input[i + 1] == '>' || input[i] == '<' && input[i + 1] == '<')
        {
            len = len + 4;
            i = i + 2;
        }
        else if (input[i] == '>' || input[i] == '<')
        {
            len = len + 3;
            i++;
        }
        else
        {
            len++;
            i++;
        }
    }
    return (len);
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
    lx_input = ft_calloc(sizeof(char), (arglen(input) + 1));
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
        else if((input[i] == '>' || input[i] == '<') && flag == 1 && flag2 == 1)
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
        else if (flag == 1 || flag2 == 1)
            lx_input[j++] = input[i];
        else if (flag == -1 || flag2 == -1)
            lx_input[j++] = input[i];
        i++;
    }
    lx_input[j] = '\0';
    return (init_cmd(lx_input, envp));
}
