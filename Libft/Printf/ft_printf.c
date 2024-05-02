/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:50:40 by luiberna          #+#    #+#             */
/*   Updated: 2024/02/12 16:43:15 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_translate(const char c, va_list *args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(*args, unsigned long int)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (c == 'u')
		return (ft_putunsigned(va_arg(*args, unsigned int)));
	else if (c == 'x')
		return (ft_puthexnbr(va_arg(*args, unsigned int), 'l'));
	else if (c == 'X')
		return (ft_puthexnbr(va_arg(*args, unsigned int), 'u'));
	else if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int					i;
	va_list				args;
	unsigned long int	res;

	i = 0;
	res = 0;
	va_start(args, s);
	while (s && s[i])
	{
		if (s[i] == '%')
		{
			res = res + ft_translate(s[++i], &args);
			if (!s[i])
				break ;
		}
		else
			res = res + ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (res);
}
