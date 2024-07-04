/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:11:10 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/14 13:59:04 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void handle_n(char **cmd, int pos)
{
	int j;

	j = 0;
	while(cmd[j])
		j++;
	while(cmd[pos])
	{
		if(pos + 1 == j)
			printf("%s", cmd[pos]);
		else
			printf("%s ", cmd[pos]);
		pos++;
	}
}

void	builtin_echo(char **cmd)
{
	int n_flag;

	
	n_flag = 0;
	if(cmd[1] && ft_strncmp(cmd[1], "-n", 2))
		n_flag = 1;
	if(n_flag == 1)
		handle_n(cmd, 2);
	else
	{
		handle_n(cmd, 1);
		printf("\n");
	}	
}

///////////////////////////////////////////////////////////////////////////////////

void	builtin_pwd(void)
{
	char cwd[PATH_MAX];

	if(getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("Error getting current directory");
		return ;
	}
}

///////////////////////////////////////////////////////////////////////////////////

void	builtin_env(t_env *env)
{
	int i;

	i = 0;
	if(!env->envp && !env->envp[0])
		perror("Error on env");
	while(env->envp[i])
	{
		if(ft_strchr(env->envp[i], '='))
			printf("%s\n", env->envp[i]);
		i++;
	}
}

///////////////////////////////////////////////////////////////////////////////////

int		ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

typedef enum e_err_msg
{
	CMD_NOT_FOUND,
	NO_FILE,
	PERM_DENIED,
	AMBIGOUS_MSG,
	TOO_MANY_ARGS,
	NUM_REQUIRED,
} err_msg;

typedef struct t_error
{
	err_msg type;
	char *msg;
} s_error;


//Precisei de mudar o tipo da funcao ft_putstr_fd para int devido aos returns

int		print_err(s_error err)
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
		e_status = print_err((s_error){NUM_REQUIRED, str});
		(free_cmd(ms), exit(e_status));
	}
	while(str[i])
	{
		res = res * 10 + (str[i] + '0');
		if(res > LONG_MAX)
		{
			e_status = print_err((s_error){NUM_REQUIRED, str});
			(free_cmd(ms), exit(e_status));
		}
		i++;
	}
	return((res * sign) % 256);
}

void	builtin_exit(t_cmd *ms, char **cmd)
{
	int e_status;

	
	if(cmd[0])
	{
		if(cmd[1] && ft_isnumber(cmd[1]))
		{
			e_status = print_err((s_error){TOO_MANY_ARGS, cmd[1]});
			(free_cmd(ms), exit(e_status));
		}
		else
			e_status = exit_atoi(ms, cmd[0]);
	}
	free_cmd(ms);
	exit(e_status);
}

///////////////////////////////////////////////////////////////////////////////////

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
			i++;
		return (s1[i] - s2[i]);
	}
	return (1);
}

int	size_of_env(char **env)
{
	int i;

	i = 0;
	while(env && env[i])
		i++;
	return (i);
}

void	sort_env(char **env, int size)
{
	int sorting;
	int i;
	char *tmp;
	
	sorting = 1;
	while(sorting)
	{
		sorting = 0;
		i = 0;
		while(i < size - 1)
		{
			if(ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				sorting = 1;
			}
			i++;
		}
		size--;
	}
}

void	print_env(t_env *env)
{
	int	i;
	int j;
	int first_equal;
	i = 0;
	
	sort_env(env->envp, size_of_env(env->envp));
	while(env->envp[i])
	{
		printf("declare -x ");
		j = 0;
		first_equal = 1;
		while(env->envp[i][j])
		{
			printf("%c", env->envp[i][j]);
			if(env->envp[i][j] == '=' && first_equal)
			{
				printf("\"");
				first_equal = 0;
			}
			j++;
		}
		printf("\"\n");
	}
}

void write_to_env(char **write, t_env *env)
{
	t_env *env_copy;
	int i;
	int j;

	env_copy = get_env(env->envp);
	i = 0;
	j = 0;
	while(env_copy->envp[i] && env_copy->envp[i])
		i++;
	while(write[j])
	{
		env_copy->envp[i] = malloc(strlen(write[j]) + 1);
		env_copy->envp[i] = ft_strdup(write[j]);
		j++;
		i++;
	}
	env = env_copy;
}

void	free_dp(char **var)
{
	int i;

	i = 0;
	while(var[i])
	{
		free(var[i]);
		i++;
	}
	free(var);
}

void	export_error(t_cmd *cmd, int i, char **str)
{
	write(2, "minishell: export: \'", 21);
	write(2, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
	write(2, "\': not a valid identifier\n", 26);
	free_dp(str);
	//Atualizar a global variable do status
}

void	builtin_export(t_env *env, t_cmd *cmd)
{
	char **env_write;
	int i;

	if(!cmd->cmd[1])
	{
		print_env(env);
		return ;
	}
	i = 0;
	
	while(cmd->cmd[i])
	{
		if(cmd->cmd[i][0] == '=')
			export_error(cmd, i, env_write);
		env_write = ft_split(cmd->cmd[i], '=');
		if(!env_write)
			(free_cmd(cmd), exit(1));
		write_to_env(env_write, env);
		i++;
	}
}

