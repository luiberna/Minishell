/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:29 by luiberna          #+#    #+#             */
/*   Updated: 2024/02/12 16:42:59 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len] && str[len] != '\n')
		len++;
	if (str && str[len] == '\n')
		len++;
	return (len);
}

char	*ft_makeline(char *str, char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	line = malloc(gnl_ft_strlen(buffer) + gnl_ft_strlen(str) + 1);
	if (!line)
		return (NULL);
	while (str && str[i])
	{
		line[i] = str[i];
		i++;
	}
	while (buffer[j] != '\n' && buffer[j])
	{
		line[i + j] = buffer[j];
		j++;
	}
	if (buffer[j] == '\n')
		line[i + j++] = '\n';
	line[i + j] = '\0';
	if (str)
		free(str);
	return (line);
}

void	clean_buffer(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && i < BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
	if (buffer[i] == '\n')
	{
		buffer[i] = '\0';
		i++;
		while (i < BUFFER_SIZE)
		{
			buffer[j] = buffer[i];
			buffer[i] = '\0';
			i++;
			j++;
		}
	}
}
