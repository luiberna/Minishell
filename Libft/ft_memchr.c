/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:01:17 by luiberna          #+#    #+#             */
/*   Updated: 2023/10/06 10:56:59 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*t;

	i = 0;
	t = (unsigned char *)s;
	while (i < n)
	{
		if (t[i] == (unsigned char)c)
			return ((void *)(&t[i]));
		else
			i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	int	c;

  char ts[] = "Ora muito bom dia!";
  c = 'a';
  printf("%s", (unsigned char *)ft_memchr(ts, c, 6));
  printf("%s", (unsigned char *)ft_memchr(ts, c, 6));
  return (0);
}
*/