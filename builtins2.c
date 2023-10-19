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

void	ft_unset2(char *str, t_global *data)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (data->envmini[i])
	{
		if (ft_strncmp(data->envmini[i], str, ft_strlen(str)) == 0)
		{
			free (data->envmini[i]);
			data->envmini[i] = NULL;
		}
		i++;
	}
	i = 0;
	while (data->env_exp[i])
	{
		if (ft_strncmp(data->env_exp[i], str, ft_strlen(str)) == 0)
		{
			free (data->env_exp[i]);
			data->env_exp[i] = NULL;
		}
		i++;
	}
}

int	ft_unset(t_lex *lex, t_global *data)
{
	while (lex->next != NULL)
	{
		lex = lex->next;
		ft_unset2(lex->content, data);
	}
	return (0);
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
