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

int	ft_unset(char **line, t_global *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line[1] == NULL)
		return (j);
	while (data->envmini[i])
	{
		if (ft_strncmp(line[1], data->envmini[i], ft_strlen(line[1])) == 0)
		{
			free(data->envmini[i]);
			data->envmini[i] = NULL;
			return (j);
		}
		i++;
	}
	return (j);
}

void	ft_moove_env(char *oldbuf, char *str, t_global *data)
{
	int			i;

	i = 0;
	while (data->envmini[i] != NULL)
	{
		if (ft_strncmp(data->envmini[i], str, 7) == 0)
		{
			free(data->envmini[i]);
			data->envmini[i] = ft_strjoin(str, oldbuf);
			data->envmini[i + 1] = NULL;
			return ;
		}
		i++;
	}
	if (data->envmini[i] == NULL)
	{
		data->envmini[i] = ft_strjoin(str, oldbuf);
		data->envmini[i + 1] = NULL;
	}
}