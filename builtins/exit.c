/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:55 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/08/08 20:42:20 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int		ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int		print_err(t_error err)
{
	if(err.type == CMD_NOT_FOUND)
		return(ft_putstr_fd(err.msg, 2), ft_putstr_fd(": command not found\n", 2));
	else if (err.type == NO_FILE)
		return(ft_putstr_fd(err.msg, 2), ft_putstr_fd(": No such file or directory\n", 2));
	else if (err.type == PERM_DENIED)
		return(ft_putstr_fd(err.msg, 2), ft_putstr_fd(": Permission denied\n", 2));
	else if (err.type == AMBIGOUS_MSG)
		return(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.msg, 2), ft_putstr_fd(" ambiguous redirect\n", 2));
	else if(err.type == TOO_MANY_ARGS)
		return(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.msg, 2), ft_putstr_fd(" too many arguments\n", 2));
	else if(err.type == NUM_REQUIRED)
		return(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.msg, 2), ft_putstr_fd(" numeric argument required\n", 2));
	return (1);
}

void ignore_space_set_sign(char *str, int *i, int *sign)
{
	while(str[*i] && str[*i] == ' ')
		(*i)++;
	if(str[*i] && (str[*i] == '-' || str[*i] == '+'))
	{
		if(str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int		exit_atoi(t_cmd *ms, char *str)
{
	int i;
	int sign;
	unsigned long res;
	int e_status;

	sign = 1;
	i = 0;
	res = 0;
	ignore_space_set_sign(str, &i, &sign);
	if(!ft_isnumber(str + i))
	{
		e_status = print_err((t_error){NUM_REQUIRED, str});
		(free_cmd(ms), exit(e_status));
	}
	while(str[i])
	{
		res = res * 10 + (str[i] - '0');
		if(res > LONG_MAX)
		{
			e_status = print_err((t_error){NUM_REQUIRED, str});
			(free_cmd(ms), exit(e_status));
		}
		i++;
	}
	return((res * sign) % 256);
}


void	builtin_exit(t_cmd *ms, char **cmd, t_env *env)
{
	int e_status;

	e_status = 0;
	if (cmd[1] && cmd[2])
	{
		write(2, "Minishell: exit: Too many arguments\n", 37);
		env->ex_code = 1;
		return ;
	}
	else if(cmd[1] && !ft_isnumber(cmd[1]))
	{
		e_status = print_err((t_error){TOO_MANY_ARGS, cmd[1]});
		(free_cmd(ms), exit(2));
	}
	else if(cmd[1])
		e_status = exit_atoi(ms, cmd[1]);
	free_cmd(ms);
	free_list(env->envp);
    free(env);
	write(1, "exit\n", 6);
	exit(e_status);
}
