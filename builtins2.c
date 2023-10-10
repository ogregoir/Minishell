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

int	ft_export2(t_global *data, char **line, int i)
{
	int	l;
	int	j;

	l = 0;
	j = 0;
	while (data->envmini[l] != NULL)
		l++;
	while (line[i][j])
	{
		if (line[i][j] == '=')
		{
			data->envmini[l] = ft_substr(line[i], 0, ft_strlen(line[i]));
			data->envmini[l + 1] = NULL;
			return (0);
		}
		j++;
	}
	return (0);
}

int	ft_already_exists(char **line, t_global *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[1][i] != '=')
		i++;
	while (data->envmini[j] != NULL)
	{
		if (ft_strncmp(line[1], data->envmini[j], i) == 0)
		{
			data->envmini[j] = NULL;
			data->envmini[j] = ft_strdup(line[1]);
			return (0);
		}
		j++;
	}
	return (0);
}

int	ft_export(char **line, t_global *data)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (line[1] == NULL)
		return (0);
	if (line[i] != NULL)
	{
		while (line[i] != NULL)
		{
			if (ft_already_exists(line, data) != 0)
				j = ft_export2(data, line, i);
			else
				j = ft_already_exists(line, data);
			i++;
		}
	}
	return (j);
}

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