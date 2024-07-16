/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:07:57 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/07/04 18:49:11 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	builtin_pwd(t_cmd *cmd)
{
	char cwd[PATH_MAX];
	int i;

	i = 1;
	if(cmd->cmd[i])
	{
		while(cmd->cmd && cmd->cmd[i])
		{
			free(cmd->cmd[i]);
			i++;
		}
	}
	if(getcwd(cwd, PATH_MAX) != NULL)
	{
		write(1, &cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		exit(0);
	}	
	else
		error_msg("Error getting current directory");
}
