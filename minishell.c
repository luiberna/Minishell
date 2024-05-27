/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:23:52 by luiberna          #+#    #+#             */
/*   Updated: 2024/05/10 15:58:53 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
    char *input;
    t_cmd *cmd;
    t_env *env;
    int i = 0;

    if (argc != 1)
        return (ft_printf("Minishell takes no args\n"), 0);
    env = get_env(envp);
    (void)argv;
    while (1) 
    {
        input = readline("DrunkShell \U0001F37A> ");
        add_history(input);
        cmd = lexer_args(input, env->envp);
        //check_cmd(cmd, env->envp);
        free(input);
    }
    return (0);
}
