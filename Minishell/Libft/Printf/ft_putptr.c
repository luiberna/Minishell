/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:50:10 by luiberna          #+#    #+#             */
/*   Updated: 2024/02/12 16:43:27 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(unsigned long int n)
{
	if (!n)
		return (ft_putstr("(nil)"));
	else
		return (ft_putstr("0x") + ft_puthexnbr(n, 'l'));
}
