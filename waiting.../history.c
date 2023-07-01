/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:02:42 by ogregoir          #+#    #+#             */
/*   Updated: 2023/07/01 13:23:27 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_history(t_historical *historic, char **line)
{
	int	j;
	int	i;

	i = 0;
	j = historic->j;
	if (!historic->str)
		ft_strlcpy(historic->str[j], line[1], ft_strlen(line[1]));
	else
		ft_strjoin_free(historic->str[j], line[1]);
	historic->str[j][ft_strlen(line[1] + 1)] = '\n';
	j++;
	historic->j = j;	
}