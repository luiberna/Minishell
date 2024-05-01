/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:57:18 by luiberna          #+#    #+#             */
/*   Updated: 2023/10/04 15:47:03 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && (i < (size - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int	main(void)
{
	char tdst[50];
	char tsrc[] = "Ora muito bom dia!";

	printf ("%zu\n", ft_strlcpy(tdst, tsrc, 6));
	printf ("%s\n", strncpy(tdst, tsrc, 6));
	return (0);
}
*/
