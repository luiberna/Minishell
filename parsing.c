/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:35:24 by luiberna          #+#    #+#             */
/*   Updated: 2024/05/10 16:36:39 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Aumenta a lenght consoante a existencia de redirections sendo que apos a redirection precisamos de um indicador
'\3' para indicar a existencia de um novo argumento para prevenir ">>>" ou ">teste" separando ">>\3>" e ">\3teste"
respetivamente*/
int     arglen(char *input)
{
    int i;
    int len;
    
    i = 0;
    len = 0;
    while (input[i])
    {
        if (input[i] == '>' && input[i + 1] == '>' || input[i] == '<' && input[i + 1] == '<')
        {
            len = len + 3;
            i = i + 2;
        }
        else if (input[i] == '>' || input[i] == '<')
        {
            len = len + 2;
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

/*Divide o input dado em comandos (divididos por pipes "|" ) e argumentos dos comandos
divididos por espacos, preservando qualquer informacao guardada dentro de aspas duplas*/
t_cmd   *lexer_args(char *input, char **envp)
{
    int flag;
    int i;
    char *lx_input;

    i = 0;
    flag = 1;
    lx_input = ft_calloc(sizeof(char), (ft_strlen(input) + 1));
    while (input[i])
    {
        if (input[i] == ' ' && flag == 1)
            lx_input[i] = '\3';
        else if (input[i] == '|' && flag == 1)
            lx_input[i] = '\4';
        else if (input[i] == '"' || input[i] == '\'')
        {
            flag *= -1;
            lx_input[i] = input[i];
        }
        else if (flag == 1)
            lx_input[i] = input[i];
        else if (flag == -1)
            lx_input[i] = input[i];
        i++;
    }
    return (init_cmd(lx_input, envp));
}
