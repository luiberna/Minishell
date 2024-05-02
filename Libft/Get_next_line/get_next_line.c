/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:26:50 by luiberna          #+#    #+#             */
/*   Updated: 2024/02/19 16:27:12 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;
	int			i;

	str = NULL;
	i = 0;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		while (i <= BUFFER_SIZE)
		{
			buffer[i] = '\0';
			i++;
		}
		return (NULL);
	}
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		str = ft_makeline(str, buffer);
		clean_buffer(buffer);
		if (str[gnl_ft_strlen(str) - 1] == '\n')
			return (str);
	}
	return (str);
}

// int	main(void)
// {
// 	int fd;
// 	char *line;
// 	int nbl = 0;

// 	fd = open("teste.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		printf("%s", line);
// 		nbl++;
// 		free(line);
// 	}
// }