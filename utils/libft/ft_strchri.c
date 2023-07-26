/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:59:18 by ogregoir          #+#    #+#             */
/*   Updated: 2023/06/13 14:59:54 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchri(const char *str, int s)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)s)
			return (i);
		i++;
	}
	if ((char)s == 0)
		return (i);
	return (-1);
}
