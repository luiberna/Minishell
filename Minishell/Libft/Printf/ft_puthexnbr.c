/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:22:10 by luiberna          #+#    #+#             */
/*   Updated: 2024/02/12 16:43:21 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexnbr(unsigned long int n, int c)
{
	char	*str;

	if (c == 'l')
		str = "0123456789abcdef";
	else if (c == 'u')
		str = "0123456789ABCDEF";
	if (n < 16)
		return (ft_putchar(str[n]));
	return (ft_puthexnbr(n / 16, c) + ft_putchar(str[n % 16]));
}
