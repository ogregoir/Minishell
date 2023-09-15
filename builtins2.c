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

int	ft_export2(char **env, char **line, int i)
{
	int	l;
	int	j;
	int	m;

	l = 0;
	j = 0;
	m = 0;
	while (env[l] != NULL)
		l++;
	while (line[i][j])
	{
		if (line[i][j] == '=')
		{
			env[l] = ft_substr(line[i], 0, ft_strlen(line[i]));
			env[l + 1] = NULL;
			return (m);
		}
		j++;
	}
	return (m);
}

int	ft_export(char **line, char **env)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (line[1] == NULL)
		return (j);
	if (line[i] != NULL)
	{
		while (line[i] != NULL)
		{
			j = ft_export2(env, line, i);
			i++;
		}
	}
	return (j);
}

int	ft_unset(char **line, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line[1] == NULL)
		return (j);
	while (env[i])
	{
		if (ft_strncmp(line[1], env[i], ft_strlen(line[1])) == 0)
		{
			free(env[i]);
			env[i] = NULL;
			return (j);
		}
		i++;
	}
	return (j);
}

