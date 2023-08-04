/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:21:26 by ogregoir          #+#    #+#             */
/*   Updated: 2023/06/30 17:45:09 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	size_t			i;
	unsigned char	*ptr12;
	unsigned char	*ptr21;

	ptr12 = ((unsigned char *)ptr1);
	ptr21 = ((unsigned char *)ptr2);
	i = 0;
	if (!size)
		return (0);
	while (ptr12[i] == ptr21[i] && i < (size - 1))
		i++;
	return ((*(unsigned char *)(ptr1 + i)) - *(unsigned char *)(ptr2 + i));
}
