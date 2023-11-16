/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:09:54 by marvin            #+#    #+#             */
/*   Updated: 2023/10/13 14:09:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	maj_env_exp(t_global *data, char *str, int i)
{
	int	j;

	j = 0;
	while (data->env_exp[j] != NULL)
	{
		if (ft_strncmp(data->env_exp[j], str, i) == 0)
			free(data->env_exp[j]);
		j++;
	}
}

char	*ft_already_exists2(t_global *data, char *str, int i)
{
	int		j;
	char	*s;

	j = 0;
	s = NULL;
	while (data->env_exp[j] != NULL)
	{
		if (ft_strncmp(data->env_exp[j], str, i) == 0)
		{
			s = ft_strdup(data->env_exp[j]);
			return (s);
		}
		j++;
	}
	return (NULL);
}

void	ft_insert_env(t_global *data, char *str, int i)
{
	int	j;

	j = 0;
	while (data->envmini[j] != NULL)
	{
		if (ft_strncmp(data->envmini[j], str, i) == 0)
		{
			free(data->envmini[j]);
			data->envmini[j] = ft_strdup(str);
			return ;
		}
		j++;
	}
	data->envmini[j] = ft_strdup(str);
	data->envmini[j + 1] = NULL;
}

int	ft_search_i(char *str)
{
	int	i;

	i = 0;
	if (ft_strchri(str, 61) != -1)
	{
		while (str[i] != '=')
			i++;
	}
	else
		i = ft_strlen(str);
	return (i);
}

void	ft_export2(t_lex *lex, t_global *data)
{
	int		i;
	char	*s;

	i = ft_search_i(lex->content);
	s = NULL;
	if (ft_already_exists(data, lex->content, i) != 1)
	{
		if (ft_strchri(lex->content, 61) != -1)
			s = ft_strdup(lex->content);
		if (ft_strchri(lex->content, 64) == -1)
			s = ft_already_exists2(data, lex->content, i);
	}
	else
	{
		if (ft_strchri(lex->content, 61) == -1)
			return ;
		ft_insert_env(data, lex->content, i);
	}
	if (s != NULL)
	{
		ft_insert_env(data, s, i);
		free(s);
	}
	maj_env_exp(data, lex->content, i);
}
