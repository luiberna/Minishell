/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:09:55 by luiberna          #+#    #+#             */
/*   Updated: 2023/10/06 10:50:52 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)(&s[len]));
		len--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int	tc;

	char test[] = "";
	tc = 'a';
	printf("%s\n", ft_strrchr(test, tc));
	printf("%s", strrchr(test, tc));
	return (0);
}
*/