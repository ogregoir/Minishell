/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:33:37 by ogregoir          #+#    #+#             */
/*   Updated: 2023/11/17 13:25:43 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_copys(size_t len, size_t j, char const *s, char *str)
{
	size_t	i;

	i = 0;
	while (s[j] && i < len)
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		j;

	j = start;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	if (len < ft_strlen (s))
		str = malloc(sizeof(char) * len + 1);
	else
		str = malloc(sizeof(char) * ft_strlen(s + start) + 1);
	if (!str)
		return (0);
	ft_copys(len, j, s, str);
	return (str);
}

char	*ft_substrfree(char *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		j;

	j = start;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	if (len < ft_strlen (s))
		str = malloc(sizeof(char) * len + 1);
	else
		str = malloc(sizeof(char) * ft_strlen(s + start) + 1);
	if (!str)
		return (0);
	ft_copys(len, j, s, str);
	free(s);
	s = NULL;
	return (str);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		j;

	j = start;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	if (len < ft_strlen (s))
		str = malloc(sizeof(char) * len + 1);
	else
		str = malloc(sizeof(char) * ft_strlen(s + start) + 1);
	if (!str)
		return (0);
	ft_copys(len, j, s, str);
	free(s);
	return (str);
}
