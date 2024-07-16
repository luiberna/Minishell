/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:45 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/07/15 12:15:37 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	command_len(char **cmd)
{
	int i;

	i = 0;
	while(cmd && cmd[i])
		i++;
	return (i);	
}

char *find_on_env(char **env, char *tofind)
{
	int i;
	char *ret;

	i = 0;
	while(env[i])
	{
		if(ft_strncmp(env[i], tofind, ft_strlen(tofind)) == 0)
		{
			ret = ft_strdup(env[i] + ft_strlen(tofind) + 1);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int save_pwd(char *var_to_update, t_env *env)
{
	char var[PATH_MAX];
	int i;
	char *tmp;

	i = 0;
	if(getcwd(var, sizeof(var)))
	{
		while(env->envp[i] && ft_strncmp(env->envp[i], var_to_update, ft_strlen(var_to_update)) != 0)
			i++;
		if(env->envp[i])
			free(env->envp[i]);
		env->envp[i] = ft_strdup(var_to_update);
		tmp = ft_strjoin("=", var);
		env->envp[i] = ft_strjoin(env->envp[i], tmp);
		free (tmp);
	}	
	return (1);
}

// Necessario atualizar o PWD e guardar um OLDPWD para o caso de apagarem a pasta onde estavamos a a executar o minishell
int	exec_cd(char *path, t_env *env)
{
	save_pwd("OLDPWD", env);
	if(chdir(path) == 0 && save_pwd("PWD", env))
		//Update Global Status para 0
		;
	else
	{
		if(access(path, F_OK) == -1)
			write(2, "minishell: cd: no such file or directory\n", 42);
		else if(access(path, R_OK | W_OK | X_OK) == -1)
			write(2, "minishell: cd: Permission denied\n", 34);
		else
			write(2,"minishell: cd: not a directory\n", 32);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		//Update Global status para 1
	}
	return (1);
}

// Casos possiveis no CD - "cd" / "cd --" / "cd -" / "cd path"

void	builtin_cd(t_env *env, t_cmd *cmd)
{
	char *home_path;
	if(command_len(cmd->cmd) > 2)
	{
		write(2, "Minishell: cd: too many arguments\n", 35);
		//Update Global status para 1 
		return ;
	}
	home_path = find_on_env(env->envp, "HOME");
	home_path = ft_strjoin(home_path, "/");
	if(!cmd->cmd[1] && exec_cd(home_path, env))
		//Update Global Status para 0 e Voltar para tras
		return ;
	else
	{
		if(ft_strcmp(cmd->cmd[1], "--") == 0 && exec_cd(home_path, env))
			//Update Global Status para 0 e Voltar para tras
			return ;
		exec_cd(cmd->cmd[1], env);
	}
}
