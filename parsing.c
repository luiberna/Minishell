/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:35:24 by luiberna          #+#    #+#             */
/*   Updated: 2024/05/02 13:29:40 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Divide o input dado em comandos (divididos por pipes "|" ) e argumentos dos comandos
divididos por espacos, preservando qualquer informacao guardada dentro de aspas duplas*/
t_cmd   *lexer_args(char *input, char **envp)
{
    int flag;
    int i;
    char *lx_input;

    i = 0;
    flag = 1;
    lx_input = malloc(sizeof(char) * (ft_strlen(input) + 1));
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
