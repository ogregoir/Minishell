/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:00:29 by ogregoir          #+#    #+#             */
/*   Updated: 2023/05/26 17:00:40 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(sizeof(*s1) * (ft_strlen(s1) + (ft_strlen(s2))) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (i <= j)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	free (s1);
	str[j] = 0;
	return (str);
}
