/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:16:08 by marvin            #+#    #+#             */
/*   Updated: 2023/10/11 12:16:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verif_exp(char *str, t_lex *lex)
{
	int	i;

	i = 0;
	if (!lex->next && ft_strchri(str, 61) == -1)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == 32)
			return (1);
		if (str[i] == 61)
			break ;
		i++;
	}
	if (ft_strchri(str, 32) != -1)
		return (2);
	return (0);
}

int	ft_export3(t_global *data, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_isalpha(str[0]) == 0)
		return (127);
	while (str[i] != '=')
		i++;
	while (data->envmini[j] != NULL)
	{
		if (ft_strncmp(data->envmini[j], str, i) == 0)
		{
			free (data->envmini[j]);
			data->envmini[j] = ft_strdup(str);
			return (0);
		}
		j++;
	}
	i = 0;
	while (data->env_exp[i] != NULL)
		i++;
	data->env_exp[i] = ft_strdup(str);
	data->env_exp[i + 1] = NULL;
	return (0);
}

void	free_env_exp(t_global *data, char *str, int i)
{
	int	j;

	j = 0;
	while (data->env_exp[j])
	{
		if (ft_strncmp(data->env_exp[j], str, i) != 0)
			free(data->env_exp[j]);
		j++;
	}
}

int	ft_already_exists(t_global *data, char *str, int i)
{
	int		j;

	j = 0;
	while (data->env_exp[j] != NULL)
	{
		if (ft_strncmp(data->env_exp[j], str, i) == 0)
			return (0);
		j++;
	}
	return (1);
}

int	ft_export(t_lex *lex, t_global *data)
{
	int	i;

	i = 0;
	if (!lex->next)
	{
		while (data->envmini[i] != NULL)
		{
			printf("declare -x %s\n", data->envmini[i]);
			i++;
		}
		return (0);
	}
	if (ft_isalpha(lex->next->content[0]) == 0)
		return (1);
	while (lex->next != NULL)
	{
		lex = lex->next;
		ft_export2(lex->content, data);
	}
	return (0);
}
