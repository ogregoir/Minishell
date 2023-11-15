/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:04:43 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/13 22:13:26 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	s;

	s = 0;
	while (s1[s] != '\0' && s2[s] != '\0' && s1[s] == s2[s])
		s++;
	return (*(unsigned char *)(s1 + s) - *(unsigned char *)(s2 + s));
}

int	ft_create_tmp(char *line, int temp)
{
	int	i;

	i = 0;
	line = ft_strjoin(line, "\n");
	while (line[i])
	{
		write(temp, &line[i], 1);
		i++;
	}
	return (temp);
}
