/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:31:46 by luiberna          #+#    #+#             */
/*   Updated: 2023/11/27 12:39:24 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tdest;
	unsigned char	*tsrc;

	tdest = (unsigned char *)dest;
	tsrc = (unsigned char *)src;
	if (!tdest && !tsrc)
		return (NULL);
	if (tsrc < tdest)
	{
		while (n-- > 0)
			tdest[n] = tsrc[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	dest[15];

	char src[] = "Ora muito bom dia!";
	printf("%s\n", (char *)ft_memmove(dest, src, 6));
	printf("%s\n", (char *)memmove(dest, src, 6));
	return (0);
}
*/