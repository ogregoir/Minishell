/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:35 by rgreiner          #+#    #+#             */
/*   Updated: 2023/06/30 14:17:37 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_check_nbr(char **str)
{
	int	i;
	int	j;
	
	i = 1;
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if(str[i][j] < '0' || str[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i] != '\0')
	{
		i++;
		free(split[i]);
	}
	free(split);
	split = NULL;
}