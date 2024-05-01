/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:50:00 by luiberna          #+#    #+#             */
/*   Updated: 2024/02/12 16:43:34 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsigned(unsigned int n)
{
	size_t	i;
	char	r;

	i = 0;
	if (n >= 10)
	{
		i = i + ft_putunsigned(n / 10);
	}
	r = n % 10 + '0';
	write(1, &r, 1);
	i++;
	return (i);
}
