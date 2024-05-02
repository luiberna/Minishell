/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:33:15 by luiberna          #+#    #+#             */
/*   Updated: 2023/10/09 14:02:07 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*temp;

	i = 0;
	temp = malloc(nmemb * size);
	if (temp == NULL)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (temp);
	while (i < (nmemb * size))
	{
		*((unsigned char *)(temp + i)) = 0;
		i++;
	}
	return ((void *)temp);
}
