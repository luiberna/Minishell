/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:12:09 by luiberna          #+#    #+#             */
/*   Updated: 2023/10/06 10:51:14 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)(&s[i]));
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int	tc;

	char test[] = "Ora muito bom dia!";
	tc = 'y';
	printf("%s\n", ft_strchr(test, tc));
	printf("%s", strchr(test, tc));
	return (0);
}
*/