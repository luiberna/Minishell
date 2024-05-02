/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:12:47 by marvin            #+#    #+#             */
/*   Updated: 2023/10/09 11:36:45 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ds;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	end = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	ds = malloc(sizeof(char) * (end - start + 1));
	if (ds == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		ds[i] = s1[start];
		i++;
		start++;
	}
	ds[i] = '\0';
	return (ds);
}
/*
int	main(void)
{
	char	*test;

	test = ft_strtrim("laOra muito bom dia!la", "la");
	printf("%s\n", test);
	free(test);
}
*/