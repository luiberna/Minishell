/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:02:58 by luiberna          #+#    #+#             */
/*   Updated: 2023/10/06 15:19:41 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((t1[i] == t2[i]) && (i < n - 1))
	{
		i++;
	}
	return (t1[i] - t2[i]);
}
/*
#include <string.h>

int	main(void)
{
	char t1[] = "abde";
	char t2[] = "abdc";
	printf("%d", ft_memcmp(t1, t2, 3));
	printf("%d", memcmp(t1, t2, 3));
	return (0);
}
*/