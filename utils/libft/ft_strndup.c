/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:11:11 by ogregoir          #+#    #+#             */
/*   Updated: 2023/07/02 19:24:04 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int n)
{
	char	*tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (n + 1));
	while (src[i])
	{
		if (i != n)
			tab[i] = src[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
