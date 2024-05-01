/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:39:01 by marvin            #+#    #+#             */
/*   Updated: 2023/10/09 14:11:41 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len(long int n)
{
	long int	tn;
	long int	len;

	tn = n;
	len = 1;
	if (n < 0)
	{
		len++;
		tn = -tn;
	}
	while (tn >= 10)
	{
		tn = tn / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	tn;
	int			len;
	char		*str;

	tn = n;
	len = n_len(tn);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (tn < 0)
	{
		str[0] = '-';
		tn = -tn;
	}
	if (tn == 0)
		str[0] = '0';
	str[len] = '\0';
	len--;
	while (len >= 0 && tn > 0)
	{
		str[len] = (tn % 10) + '0';
		tn = tn / 10;
		len--;
	}
	return (str);
}
/*
int	main(void)
{
	char	*test;

	test = ft_itoa(1);
	printf("%s\n", test);
	free(test);
	return (0);
}
*/