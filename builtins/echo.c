/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:59 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/07/04 19:06:45 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_flag(char *arg)
{
	int i;

	i = 1;
	if(arg[0] != '-')
		return (0);
	while(arg[i] && arg[i] == 'n')
		i++;
	if(arg[i] == '\0')
		return (1);
	return (0);
}

void print_echo(char **cmd, int n_flag, int i)
{
	if(!cmd[i])
	{
		if(!n_flag)
			write(1, "\n", 1);
		return ;
	}
	while(cmd[i])
	{
		printf("%s", cmd[i]);
		if(cmd[i + 1])
			printf(" ");
		else if(!cmd[i + 1] && !n_flag)
			printf("\n");
		i++;
	}
}

void	builtin_echo(char **cmd)
{
	int n_flag;
	int i;

	i = 1;
	n_flag = 0;
	while(cmd[i] && check_flag(cmd[i]))
	{
		n_flag = 1;
		i++;
	}
	print_echo(cmd, n_flag, i);
	//Update global Var para 1
}