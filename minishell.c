/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:23:52 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/09 17:14:19 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_ex_code;

int main (int argc, char **argv, char **envp)
{
    char *input;
    t_cmd *cmd;
    t_env *env;
    
    (void)argv;
    if (argc != 1)
        return (ft_printf("Minishell takes no args\n"), 0);
    env = get_env(envp);
    while (1) 
    {
        signals_default(env);
        input = readline("DrunkShell> ");
        if (input && *input)
        {
            add_history(input);
            cmd = lexer_args(input, env);
            if (cmd)
            {
                expander(cmd, env);
                remove_quotes(cmd);
                pipes_exec(cmd, env);
                free_cmd(cmd);
            }
            free(input);
        }
        else if (!input)
        {
            printf("exit\n");
            break ;
        }
    }
    free_list(env->envp);
    free(env);
    return (0);
}
