/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:49:48 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/09 17:15:05 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quit(int sign)
{
	pid_t	pid;
	int		status;

	(void)sign;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		rl_replace_line("   ", 0);
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
    g_ex_code = 130;
	if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
void	signals_default_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signals_default(t_env *env)
{
	signal(SIGINT, handle_sign);
	signal(SIGQUIT, SIG_IGN);
}
