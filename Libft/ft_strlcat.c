/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:35:25 by luiberna          #+#    #+#             */
/*   Updated: 2023/10/04 17:09:01 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[len])
		len++;
	while (src[i] && ((i + len) < (size - 1)))
	{
		dst[i + len] = src[i];
		i++;
	}
	dst[i + len] = '\0';
	if (size < len)
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + len);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char tdst[20] = "Ora muito ";
	char tsrc[] = "bom dia!";
	printf("%ld\n", ft_strlcat(tdst, tsrc, 2));
	printf("%s", strncat(tdst, tsrc, 2));
	return (0);
}
*/