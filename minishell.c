/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:23:52 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/07 19:40:08 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *g_env;

void	handle_quit(int sign)
{
	pid_t	pid;
	int		status;

	(void)sign;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		rl_replace_line("  ", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sign(int sign)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	(void)sign;
	write(2, "\n", 1);
    if (g_env)
        g_env->ex_code = 130;
	if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals_default(t_env *env)
{
	signal(SIGINT, handle_sign);
	signal(SIGQUIT, handle_quit);
}

int main (int argc, char **argv, char **envp)
{
    char *input;
    t_cmd *cmd;
    
    (void)argv;
    if (argc != 1)
        return (ft_printf("Minishell takes no args\n"), 0);
    g_env = get_env(envp);
    while (1) 
    {
        signals_default(g_env);
        input = readline("DrunkShell> ");
        if (input && *input)
        {
            add_history(input);
            cmd = lexer_args(input, g_env);
            if (cmd)
            {
                expander(cmd, g_env);
                remove_quotes(cmd);
                pipes_exec(cmd, g_env);
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
    free_list(g_env->envp);
    free(g_env);
    return (0);
}
