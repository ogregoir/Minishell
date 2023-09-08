/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:59:35 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 18:59:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **line, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if (ft_strchr(line[1], '=') != 0)
	{
		env[i] = ft_substr(line[1], 0, ft_strlen(line[1]));
		env[i + 1] = NULL;
	}
	else
		return ;
}

void	ft_unset(char **line, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(line[1], env[i], ft_strlen(line[1])) == 0)
		{
			free(env[i]);
			env[i] = NULL;
		}
		i++;
	}
}

