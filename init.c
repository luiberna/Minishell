/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:51 by luiberna          #+#    #+#             */
/*   Updated: 2024/06/14 17:12:23 by luiberna         ###   ########.fr       */
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
	while (envp[0] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
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
t_cmd   *create_cmd(char *sep_cmd, t_cmd *prev_cmd, int i, char **envp)
{
    t_cmd *cmd;
    int j;
    
    j = 0;
    cmd = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd = ft_split(sep_cmd, '\3');
    while (cmd->cmd[j] && (cmd->path = get_path(cmd->cmd[j], envp)) == NULL)
        j++;
    cmd->nb_cmds = i + 1;
    if (cmd->nb_cmds == 1)
        cmd->prev = NULL;
    else
        cmd->prev = prev_cmd;
    cmd->next = NULL;
    cmd->fd[0] = 0;
    cmd->fd[1] = 1;
    cmd->fd_redirect[0] = 0;
    cmd->fd_redirect[1] = 1;
    cmd->pid = 0;
    return(cmd);
}

/*Inicializa a double linked list (struct t_cmd) criando todas as nodes com a informacao
necessaria a cada comando*/
t_cmd    *init_cmd(char *input, char **envp)
{
    t_cmd *fst_cmd;
    t_cmd *curr_cmd;
    char **sep_cmd;
    int i;

    i = 1;
    if (input[0] == '\0')
        return (NULL);
    sep_cmd = ft_split(input, '\4');
    fst_cmd = create_cmd(sep_cmd[0], NULL, 0, envp);
    curr_cmd = fst_cmd;
    while(sep_cmd[i])
    {
        curr_cmd->next = create_cmd(sep_cmd[i], curr_cmd, i, envp);
        curr_cmd = curr_cmd->next;
        i++;
    }
    return(fst_cmd);
}
