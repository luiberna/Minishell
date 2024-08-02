/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:51 by luiberna          #+#    #+#             */
/*   Updated: 2024/08/02 18:25:47 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Procura a path correta para a execucao de um comando no env*/
char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	*join_path;
	char	**paths;

	i = 0;
	while (envp[0] && envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
    if (!envp[i])
        return(NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		join_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(join_path, cmd);
		free(join_path);
		if (access(path, F_OK) == 0)
			return (free_list(paths), path);
		free(path);
		i++;
	}
	return (free_list(paths), NULL);
}

/*Cria uma node (cmd) com toda a informacao necessaria para o comando.
O pipe (fd) pode ser inicializado com valores 0 e 1 pois vao ser alterados mais tarde.
O PID pode ser inicializado com valor 0 pois vai ser alterado quando utilizarmos a fork()*/
t_cmd   *create_cmd(char *sep_cmd, int i, char **envp)
{
    t_cmd *cmd;
    int j;
    
    j = 0;
    cmd = ft_calloc(sizeof(t_cmd), 1);
    if (!cmd)
        return (NULL);
    cmd->cmd = ft_split(sep_cmd, '\3');
    while (cmd->cmd[j] && (cmd->path = get_path(cmd->cmd[j], envp)) == NULL)
        j++;
    if (ft_strncmp(cmd->cmd[0], "./", 2) == 0)
        cmd->path = ft_strdup(cmd->cmd[0]);
    cmd->nb_cmds = i + 1;
    cmd->next = NULL;
    cmd->fd[0] = -1;
    cmd->fd[1] = -1;
    cmd->pid = 0;
    return(cmd);
}
/*Para verificar alguns erros como "ls |   | pwd" ou "   | pwd"*/
int check_input(char *input, t_env *env)
{
    int i;
    int prev_pipe;
    
    i = 0;
    prev_pipe = 1;
    while (input[i])
    {
        while (input[i] == '\3')
            i++;
        if (input[i] == '\4')
        {
            if (prev_pipe)
                return (env->ex_code = 2, write(2, "syntax error near unexpected token '|'\n", 40), 0);
            prev_pipe = 1;
        }
        else if (input[i] != '\0')
            prev_pipe = 0;
        i++;
    }
    if (prev_pipe)
        return (env->ex_code = 2, write(2, "syntax error near unexpected token 'newline'\n", 46), 0);
    return 1;
}

/*Inicializa a double linked list (struct t_cmd) criando todas as nodes com a informacao
necessaria a cada comando*/
t_cmd    *init_cmd(char *input, t_env *env)
{
    t_cmd *fst_cmd;
    t_cmd *curr_cmd;
    char **sep_cmd;
    int i;

    i = 1;
    if (input[0] == '\0')
        return (NULL);
    if (check_input(input, env) == 0)
        return(free(input), NULL);
    else
    {
        sep_cmd = ft_split(input, '\4');
        fst_cmd = create_cmd(sep_cmd[0], 0, env->envp);
        curr_cmd = fst_cmd;
        while(sep_cmd[i])
        {
            curr_cmd->next = create_cmd(sep_cmd[i], i, env->envp);
            curr_cmd = curr_cmd->next;
            i++;
        }
    }
    free(input);
    return(free_list(sep_cmd), fst_cmd);
}
