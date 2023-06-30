/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:58 by rgreiner          #+#    #+#             */
/*   Updated: 2023/06/30 14:18:10 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_exit(char **line)
{
	printf("exit\n");
	if (line[1] == NULL)
		exit (0);
	if (ft_check_nbr(line) == 1)
		{
			printf("bash: exit: %s numeric argument required\n", line[1]);
			exit (1);
		}
	else
		exit (ft_atoi(line[1]));
}