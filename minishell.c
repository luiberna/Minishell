/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:23:52 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/01 18:45:19 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_quit(int sign)
{
	pid_t	pid;
	int		status;

	(void)sign;
	pid = waitpid(-1, &status, 0);
	if (pid == -1)
	{
		write(2, "Quit: 3\n", 8);  // Display quit message
	}
}

void	handle_sign(int sign)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	(void)sign;
	write(2, "\n", 1);  // Print new line for Ctrl+C
	if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals_default(void)
{
	signal(SIGINT, handle_sign);
	signal(SIGQUIT, handle_quit);
}

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
        signals_default();
        input = readline("DrunkShell> ");
        if (input && *input)
        {
            add_history(input);
            cmd = lexer_args(input, env->envp);
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
            write(1, "\n", 1);
            break ;
        }
    }
    free_list(env->envp);
    free(env);
    return (0);
}
