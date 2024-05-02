/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:17:14 by marvin            #+#    #+#             */
/*   Updated: 2023/10/09 16:17:19 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	len;

	len = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			len++;
		while (*s != c && *s)
			s++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**rstr;
	size_t	len;
	int		i;

	i = 0;
	rstr = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!rstr || !s)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				len = ft_strlen(s);
			else
				len = ft_strchr(s, c) - s;
			rstr[i++] = ft_substr(s, 0, len);
			s = s + len;
		}
	}
	rstr[i] = NULL;
	return (rstr);
}
/*
int	main(void)
{
	int		index;
	char	**split;

	split = ft_split("teste de string 4     ", ' ');
	index = 0;
	while (split[index])
	{
		printf("%s\n", split[index]);
		index++;
	}
	free(split);
}
*/