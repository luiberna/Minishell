/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:53 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/08/09 17:15:40 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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
	int i;
	int swapping;
	char *tmp;
	swapping = 1;
	while(swapping)
	{
		i = 0;
		swapping = 0;
		while(i < size - 1)
		{
			if(ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				swapping = 1;
			}
			i++;
		}
		size--;
	}	
	
}

void	print_env2(t_cmd *cmd, t_env *env)
{
	int	i;
	int j;
	int first_equal;
	
	i = 0;
	sort_env(env->envp, size_of_env(env->envp));
	while(env->envp[i])
	{
		write(1, "declare -x ", 12);
		j = -1;
		first_equal = 1;
		while(env->envp[i][++j])
		{
			write(1, &env->envp[i][j], 1);
			if(env->envp[i][j] == '=' && first_equal)
			{
				write(1, "\"", 2);
				first_equal = 0;
			}
		}
		if(ft_strchr(env->envp[i], '='))
			write(1, "\"", 2);
		write(1, "\n", 2);
		i++;
	}
}

void	print_env(t_cmd *cmd, t_env *env)
{
	int	i;
	int j;
	int first_equal;
	
	i = 0;
	sort_env(env->envp, size_of_env(env->envp));
	while(env->envp[i])
	{
		write(cmd->fd[1], "declare -x ", 12);
		j = -1;
		first_equal = 1;
		while(env->envp[i][++j])
		{
			write(cmd->fd[1], &env->envp[i][j], 1);
			if(env->envp[i][j] == '=' && first_equal)
			{
				write(cmd->fd[1], "\"", 2);
				first_equal = 0;
			}
		}
		if(ft_strchr(env->envp[i], '='))
			write(cmd->fd[1], "\"", 2);
		write(cmd->fd[1], "\n", 2);
		i++;
	}
}

void	export_error(t_cmd *cmd, int i, char **str, t_env *env)
{
	write(2, "minishell: export: \'", 21);
	write(2, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
	write(2, "\': not a valid identifier\n", 26);
	g_ex_code = 1;
	return ;
}

int find_eq(char *str)
{
	int i; 

	i = -1;
	while (str[++i])
	 if (str[i] == '=')
	 	return (i);
	return (0);
}

void handle_no_value(char *var, t_env *env)
{
    int i;
    int size;
    char **new_envp;

	i = 0;
    size = size_of_env(env->envp);
    new_envp = (char **)malloc((size + 2) * sizeof(char *));
    if (!new_envp)
        return;
    while(i < size)
	{
        new_envp[i] = env->envp[i];
		i++;
	}
    new_envp[size] = ft_strdup(var);
    new_envp[size + 1] = NULL;
    free(env->envp);
    env->envp = new_envp;
}

void	duplicate_env(t_env *env, int size, char *new_var)
{
	char **new_envp;
	int i;
	
    new_envp = (char **)malloc((size + 2) * sizeof(char *));
    if (!new_envp)
        return;
	i = 0;
    while(i < size)
	{
		new_envp[i] = env->envp[i];
		i++;
	}
    new_envp[size] = new_var;
    new_envp[size + 1] = NULL;
    free(env->envp);
    env->envp = new_envp;	
}

void var_exists(char *var, char *value, t_env *env)
{
    int i;
    int size;
    char *new_var;
    
    if (!value)
    {
        handle_no_value(var, env);
        return;
    }
	i = 0;
    size = size_of_env(env->envp);
    new_var = ft_strjoin(var, value);
	while(i < size)
	{
        if (!ft_strncmp(var, env->envp[i], ft_strlen(var)) && env->envp[i][ft_strlen(var)] == '=')
        {
            free(env->envp[i]);
            env->envp[i] = new_var;
            return;
        }
		i++;
	}
	duplicate_env(env, size, new_var);
}

void export(t_env *env, t_cmd *cmd, int i)
{
	int j;
	int eq;
	char *var;

	eq = find_eq(cmd->cmd[i]);
	if (eq == 0)
	{
		var = ft_strdup(cmd->cmd[i]); 
		var_exists(var, NULL, env);
	}
	else
	{
		cmd->cmd[i][eq] = 0;
		var = ft_strdup(cmd->cmd[i]);
		cmd->cmd[i][eq] = '=';
		var_exists(var, cmd->cmd[i] + eq, env);
	}
	free(var);
}

int sue(char *str, char c)
{
	int i;

	i = 0;
	while(str && str[i] && str[i] != '=')
	{
		if(str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	error_handler(char *cmd)
{
	if(!cmd[0] || cmd[0] == '=' || (cmd[0] == '_' && cmd[1] == '=') || ft_isdigit(cmd[0]) || sue(cmd, '-') || sue(cmd, '.') || 
		sue(cmd, ':') || sue(cmd, ',') || sue(cmd, '\\') || sue(cmd, '!') || sue(cmd, '?'))
		return 1;
	return 0;
}

void	builtin_export(t_env *env, t_cmd *cmd)
{
	int i;

	if(!cmd->cmd[1] && cmd->next)
		print_env(cmd, env);
	else if(!cmd->cmd[1] && !cmd->next)
		print_env2(cmd, env);
	i = 1;
	while(cmd->cmd && cmd->cmd[i])
	{
		if(error_handler(cmd->cmd[i]))
		{
			export_error(cmd, i, cmd->cmd, env);
			return ;
		}
		else
			export(env, cmd, i);
		i++;
	}
}
