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

int	ft_strlen_data_env(t_global *data)
{
	int	count;

	count = 0;
	while (data->envmini[count] != NULL)
		count++;
	return (count);
}

void	ft_insert_env(t_global *data, char *str, int i)
{
	int		j;
	char	**new_envmini;

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
	new_envmini = malloc(sizeof(char *) * (ft_strlen_data_env(data) + 2));
	j = 0;
	while (data->envmini[j])
	{
		new_envmini[j] = ft_strdup(data->envmini[j]);
		j++;
	}
	new_envmini[j] = ft_strdup(str);
	new_envmini[j + 1] = NULL;
	ft_free_data_envmini(data);
	data->envmini = new_envmini;
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

char	**ft_export2(t_lex *lex, t_global *data)
{
	int		i;
	char	*s;

	i = ft_search_i(lex->content);
	s = NULL;
	if (ft_already_exists(data, lex->content, i) != 1)
	{
		if (ft_strchri(lex->content, 61) != -1)
			s = ft_strdup(lex->content);
		if (ft_strchri(lex->content, 61) == -1)
			s = ft_already_exists2(data, lex->content, i);
		ft_insert_env(data, s, i);
		free(s);
		return (data->envmini);
	}
	else if (ft_strchri(lex->content, 61) == -1)
		return (data->envmini);
	else
	{
		if (ft_strchri(lex->content, 61) == -1)
			return (data->envmini);
		ft_insert_env(data, lex->content, i);
	}
	return (data->envmini);
}
